/*
Copyright (C) 2019 wyuinche

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
<?php
  include('dbconn.php');
?>

<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title>Music List</title>
    <link rel="stylesheet" href="style.css">
    <style>
      #fake {
        display:none;
      }
    </style>

  </head>
  <body>
    <div class="music-header">
      <div class="music-title">
        <h1>Music List</h1>
      </div>
      <div class="music-nav">
        <?php
          $user_id = $_SESSION['ss_user_id'];
        ?>
        <p>Hello, <?php echo $user_id?></p>
        <button id='mypage' type="button" name="button"><a href="mypage.php">My Page</a></button>
        <button id='signout' type="button" name="button"><a href="sign_out.php">Sign Out</a></button>
        <button id='musiclist' type="button" name="button"><a href="music_main.php">Music List</a></button>
        <?php
          $sql_license ="select * from user where u_id='$user_id'";
          $rst_license = mysqli_query($conn, $sql_license);
          $license = mysqli_fetch_assoc($rst_license);
          if($license['license']=='manager') {
        ?>
          <button id='add_music' type="button" name="button"><a href="add_music.php">Add Music</a></button>
          <button id='userlist' type="button" name="button"><a href="mgr_user.php">User List</a></button>
        <?php }
        else {
          ?>
          <button id='buy' type="button" name="button"><a href="buy.php">Buy Membership</a></button>
        <?php } ?>
      </div>
    </div>

    <div class="music-list">
      <div class="music-search">
        <h3>Search Music</h3>
        <form class="music-search-form" action="music_main.php" method="post">
          <input id='music-text-input' type="text" name="music-search-text" value=""><br>
          <input id='search' type="checkbox" name="music-ck-title" value="ok" onclick="checking1(this);" checked>title
          <input id='search' type="checkbox" name="music-ck-artist" value="ok" onclick="checking1(this);">artist<br>
          <input id='sort' type="checkbox" name="music-ck-asc" value="ok" onclick="checking2(this);" checked>asc
          <input id='sort' type="checkbox" name="music-ck-des" value="ok" onclick="checking2(this);">des
          <input id='sort' type="checkbox" name="music-ck-rec-r" value="ok" onclick="checking2(this);"> recent released-date
          <input id='sort' type="checkbox" name="music-ck-old-r" value="ok" onclick="checking2(this);"> old released-date
          <input type="submit" name="music-search-submit" value="Search">
      </div>
    </form>
      <div class="music-cards">
        <table id='table1'>
          <thead>
            <tr>
              <th></th>
              <th>Title</th>
              <th>Artist</th>
              <th>Released Date</th>
              <th>Genre</th>
              <th></th>
            </tr>
          </thead>
          <tbody>
            <?php
            if(!isset($_POST['music-search-text'])){
                $sql = "select m.m_id, v.a_id, v.artist_id, m.m_title, v.artist_name, v.r_date, v.genre from music m, (select a_id, artist.artist_id, artist_name, r_date, genre from artist, album where artist.artist_id = album.artist_id) v where m.a_id = v.a_id order by m.m_title asc";
                $rst = mysqli_query($conn, $sql);
              for($i = 0; $music = mysqli_fetch_assoc($rst);$i++) {?>
              <tr>
                <td><?php echo $i+1; ?></td>
                <td>
                  <form class="music-des" action="music_description.php" method="post">
                    <?php if($license['license']=="manager") { ?> m_id <?php }?> <input class='info-id'<?php if($license['license']=="general") { ?> id='fake' <?php }?> type="text" name="music-id" value="<?php echo $music['m_id']; ?>"> <br>
                    <?php if($license['license']=="manager") { ?> a_id <?php }?> <input class='info-id' <?php if($license['license']=="general") { ?> id='fake' <?php }?> type="text" name="album-id" value="<?php echo $music['a_id']; ?>">  <br>
                    <?php if($license['license']=="manager") { ?> artist_id <?php }?> <input class='info-id' <?php if($license['license']=="general") { ?> id='fake' <?php }?> type="text" name="submit" value="<?php echo $music['artist_id']; ?>">
                    <input type="submit" name="submit" value="<?php echo $music['m_title']; ?>">
                  </form>
                </td>
                <td><?php echo $music['artist_name']; ?></td>
                <td><?php echo $music['r_date']; ?></td>
                <td><?php echo $music['genre']; ?></td>
                <td>
                  <div class="music-list">
                    <?php $music_id = $music['m_id']?>
                    <form class="like" action="like.php" method="post">
                      <input id="fake" type="text" name="like-id" value="<?php echo $music_id; ?>">
                      <input type="submit" name="like-list" value="Include to like-list">
                    </form>
                    <form class="down" action="down.php" method="post">
                      <input id="fake" type="text" name="down-id" value="<?php echo $music_id; ?>">
                      <input type="submit" name="down-list" value="Include to down-list">
                    </form>
                  </div>
                </td>
              </tr>
           <?php }
            } else {
             $target_music = trim($_POST['music-search-text']);
             if(isset($_POST['music-ck-title']))
             {
               if(isset($_POST['music-ck-asc']))
               {
                 $sql_target = "select m.m_id, v.a_id, v.artist_id, m.m_title, v.artist_name, v.r_date, v.genre from music m, (select a_id, artist.artist_id, artist_name, r_date, genre from artist, album where artist.artist_id = album.artist_id) v where m.a_id = v.a_id and m.m_title like '%$target_music%' order by m.m_title asc";
               }
               else if(isset($_POST['music-ck-des'])){
                 $sql_target = "select m.m_id, v.a_id, v.artist_id, m.m_title, v.artist_name, v.r_date, v.genre from music m, (select a_id, artist.artist_id, artist_name, r_date, genre from artist, album where artist.artist_id = album.artist_id) v where m.a_id = v.a_id and m.m_title like '%$target_music%' order by m.m_title desc";
               }
               else if(isset($_POST['music-ck-rec-r'])){
                 $sql_target = "select m.m_id, v.a_id, v.artist_id, m.m_title, v.artist_name, v.r_date, v.genre from music m, (select a_id, artist.artist_id, artist_name, r_date, genre from artist, album where artist.artist_id = album.artist_id) v where m.a_id = v.a_id and m.m_title like '%$target_music%' order by v.r_date desc";
               }
               else{
                 $sql_target = "select m.m_id, v.a_id, v.artist_id, m.m_title, v.artist_name, v.r_date, v.genre from music m, (select a_id, artist.artist_id, artist_name, r_date, genre from artist, album where artist.artist_id = album.artist_id) v where m.a_id = v.a_id and m.m_title like '%$target_music%' order by v.r_date asc";
               }
             }
             else{
               if(isset($_POST['music-ck-asc']))
               {
                 $sql_target = "select m.m_id, v.a_id, v.artist_id, m.m_title, v.artist_name, v.r_date, v.genre from music m, (select a_id, artist.artist_id, artist_name, r_date, genre from artist, album where artist.artist_id = album.artist_id) v where m.a_id = v.a_id and v.artist_name like '%$target_music%' order by v.artist_name asc";
               }
               else if(isset($_POST['music-ck-des'])) {
                 $sql_target = "select m.m_id, v.a_id, v.artist_id, m.m_title, v.artist_name, v.r_date, v.genre from music m, (select a_id, artist.artist_id, artist_name, r_date, genre from artist, album where artist.artist_id = album.artist_id) v where m.a_id = v.a_id and v.artist_name like '%$target_music%' order by v.artist_name desc";
               }
               else if(isset($_POST['music-ck-rec-r'])){
                 $sql_target = "select m.m_id, v.a_id, v.artist_id, m.m_title, v.artist_name, v.r_date, v.genre from music m, (select a_id, artist.artist_id, artist_name, r_date, genre from artist, album where artist.artist_id = album.artist_id) v where m.a_id = v.a_id and v.artist_name like '%$target_music%' order by v.r_date desc";
               }
               else{
                 $sql_target = "select m.m_id, v.a_id, v.artist_id, m.m_title, v.artist_name, v.r_date, v.genre from music m, (select a_id, artist.artist_id, artist_name, r_date, genre from artist, album where artist.artist_id = album.artist_id) v where m.a_id = v.a_id and v.artist_name like '%$target_music%' order by v.r_date asc";
               }
             }
             $rst_target = mysqli_query($conn, $sql_target);
             for($i=0; $music = mysqli_fetch_assoc($rst_target); $i++){
             ?>
                 <tr>
                   <td><?php echo $i+1; ?></td>
                   <td>
                     <form class="music-des" action="music_description.php" method="post">
                       <?php if($license['license']=="manager") { ?> m_id <?php }?> <input class='info-id' <?php if($license['license']=="general") { ?> id='fake' <?php }?> type="text" name="music-id" value="<?php echo $music['m_id'] ?>"> <br>
                       <?php if($license['license']=="manager") { ?> a_id <?php }?> <input class='info-id' <?php if($license['license']=="general") { ?> id='fake' <?php }?> type="text" name="album-id" value="<?php echo $music['a_id'] ?>">  <br>
                       <?php if($license['license']=="manager") { ?> artist_id <?php }?> <input class='info-id' <?php if($license['license']=="general") { ?> id='fake' <?php }?> type="text" name="submit" value="<?php echo $music['artist_id'] ?>">
                       <input type="submit" name="submit" value="<?php echo $music['m_title']; ?>">
                     </form>
                   </td>
                   <td><?php echo $music['artist_name']; ?></td>
                   <td><?php echo $music['r_date']; ?></td>
                   <td><?php echo $music['genre']; ?></td>
                   <td>
                     <div class="music-list">
                       <?php $music_id = $music['m_id']?>
                       <form class="like" action="like.php" method="post">
                         <input id="fake" type="text" name="like-id" value="<?php echo $music_id; ?>">
                         <input type="submit" name="like-list" value="Include to like-list">
                       </form>
                       <form class="down" action="down.php" method="post">
                         <input id="fake" type="text" name="down-id" value="<?php echo $music_id; ?>">
                         <input type="submit" name="down-list" value="Include to down-list">
                       </form>
                     </div>
                   </td>
              </tr>
            <?php
              }
            }
            ?>
          </tbody>
        </table>
        <?php mysqli_close($conn); ?>
      </div>
    </div>
    <script type="text/javascript">
      function checking1(x) {
        let box = document.getElementsById("search");
        for(let i=0; i<box.length; i++){
          if(box[i] != x){
              box[i].checked = false;
          }
        }
      };
      function checking2(x) {
        let box = document.getElementsById("sort");
        for(let i=0; i<box.length; i++){
          if(box[i] != x){
              box[i].checked = false;
          }
        }
      };
    </script>
  </body>
</html>
