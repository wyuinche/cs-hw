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
    <title>Mypage</title>
    <style media="screen">
      #fake {
        display: none;
      }
    </style>
  </head>
  <body>
    <div class="mypage-header">
      <div class="mypage-title">
        <h1>Mypage</h1>
      </div>
      <div class="mypage-nav">
        <?php
          $user_id = $_SESSION['ss_user_id'];
        ?>
        <p>Hello, <?php echo $user_id?></p>
        <button id='mypage' type="button" name="button"><a href="mypage.php">My Page</a></button>
        <button id='signout' type="button" name="button"><a href="sign_out.php">Sign Out</a></button>
        <button id='musiclist' type="button" name="button"><a href="music_main.php">Music List</a></button>
      </div>
    </div>
    <?php
      $sql = "select * from user where u_id='$user_id'";
      $rst = mysqli_query($conn, $sql);
      $user = mysqli_fetch_assoc($rst);
    ?>
    <div class="mypage-info">
      <div class="mypage-info-header">
        <h1>User Information</h1>
      </div>
      <div class="mypage-info-body">
        <table>
          <tr>
            <td>User ID</td>
            <td><?php echo $user['u_id']; ?></td>
          </tr>
          <tr>
            <td>Email</td>
            <td><?php echo $user['email']; ?></td>
          </tr>
          <tr>
            <td>Gender</td>
            <td><?php echo $user['gender']; ?></td>
          </tr>
          <tr>
            <td>License</td>
            <td><?php echo $user['license']; ?></td>
          </tr>
        </table>
      </div>
    </div>

    <?php if($user['license']=='general') { ?>
    <div class="like-list">
      <div class="most-like-list">
        <h1>Most Like List</h1>
        <?php
          $sql_most = "select m_title, a_title, artist_name, genre from
          (select a_id, a_title, artist_name, genre from artist, album where album.artist_id=artist.artist_id) tar1,
          (select a_id, m_title, like_order from like_list, music where u_id='$user_id' and count=1 and like_list.m_id = music.m_id) tar2
          where tar1.a_id=tar2.a_id order by like_order asc
          ";
          $rst_most = mysqli_query($conn, $sql_most);?>
          <table>
            <thead>
              <tr>
                <th></th>
                <th>Title</th>
                <th>Album</th>
                <th>Artist</th>
                <th>Genre</th>
              </tr>
            </thead>
            <tbody>
          <?php for($i=1; $most = mysqli_fetch_assoc($rst_most); $i++){?>
              <tr>
                <th><?php echo $i; ?></th>
                <th><?php echo $most['m_title']; ?></th>
                <th><?php echo $most['a_title']?></th>
                <th><?php echo $most['artist_name']; ?></th>
                <th><?php echo $most['genre']?></th>
              </tr>
          <?php }?>
              </tbody>
            </table>
      </div>
      <div class="just-like-list">
            <h1>Favorite List</h1>
          <?php
            $sql_just = "select m_id, m_title, a_title, artist_name, genre from
            (select a_id, a_title, artist_name, genre from artist, album where album.artist_id=artist.artist_id) tar1,
            (select like_list.m_id, a_id, m_title, like_order from like_list, music where u_id='$user_id' and like_list.m_id = music.m_id) tar2
            where tar1.a_id=tar2.a_id order by like_order asc
            ";
            $rst_just = mysqli_query($conn, $sql_just);?>
            <table>
              <thead>
                <tr>
                  <th></th>
                  <th>Title</th>
                  <th>Album</th>
                  <th>Artist</th>
                  <th>Genre</th>
                  <th></th>
                </tr>
              </thead>
              <tbody>
            <?php for($i=1; $just = mysqli_fetch_assoc($rst_just); $i++){?>
                <tr>
                  <th><?php echo $i; ?></th>
                  <th><?php echo $just['m_title']; ?></th>
                  <th><?php echo $just['a_title']?></th>
                  <th><?php echo $just['artist_name']; ?></th>
                  <th><?php echo $just['genre']?></th>
                  <th>
                    <form class="most-include" action="most.php" method="post">
                      <input id="fake" type="text" name="most-music-id" value="<?php echo $just['m_id']; ?>">
                      <input type="submit" name="submit" value="Most Like">
                    </form>
                  </th>
                </tr>
            <?php }?>
                </tbody>
              </table>
      </div>
    </div>
    <div class="down-list">
      <h1>Download List</h1>
      <?php
        $sql_down = "select m_title, a_title, artist_name, genre from
        (select a_id, a_title, artist_name, genre from artist, album where album.artist_id=artist.artist_id) tar1,
        (select a_id, m_title, down_order from download_list, music where u_id='$user_id' and download_list.m_id = music.m_id) tar2
        where tar1.a_id=tar2.a_id order by down_order asc
        ";
        $rst_down = mysqli_query($conn, $sql_down);?>
        <table>
          <thead>
            <tr>
              <th></th>
              <th>Title</th>
              <th>Album</th>
              <th>Artist</th>
              <th>Genre</th>
              <th></th>
            </tr>
          </thead>
          <tbody>
        <?php for($i=1; $down = mysqli_fetch_assoc($rst_down); $i++){?>
            <tr>
              <th><?php echo $i; ?></th>
              <th><?php echo $down['m_title']; ?></th>
              <th><?php echo $down['a_title']?></th>
              <th><?php echo $down['artist_name']; ?></th>
              <th><?php echo $down['genre']?></th>

            </tr>
        <?php }?>
            </tbody>
          </table>
    </div>

  <?php } ?>
  <?php mysqli_close($conn); ?>
  </body>
</html>
