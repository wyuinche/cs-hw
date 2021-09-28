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
  error_reporting(0);
?>

<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title>User List</title>
    <style>
      #fake {
        display:none;
      }
    </style>
  </head>
  <body>
    <div class="mgr-header">
      <div class="mgr-title">
        <h1>User List</h1>
        <p>This page is for managing user information.</p>
      </div>
      <div class="mgr-nav">
        <?php
          $user_id = $_SESSION['ss_user_id'];
        ?>
        <p>Hello, <?php echo $user_id?></p>
        <button id='mgr-mypage' type="button" name="button"><a href="mypage.php">My Page</a></button>
        <button id='mgr-signout' type="button" name="button"><a href="sign_out.php">Sign Out</a></button>
        <button id='musiclist' type="button" name="button"><a href="music_main.php">Music List</a></button>
        <button id='userlist' type="button" name="button"><a href="mgr_user.php">User List</a></button>

      </div>
    </div>
    <div class="mgr-user">
      <div class="mgr-user-search">
        <form class="mgr-user-form" action="mgr_user.php" method="post">
          <input type="text" name="user-search-text" value=""><br>
          <input id = "fake" type="text" name="delete" value="">
          <input type="submit" name="user-search-submit" value="Search">
      </div>
    </form>
      <div class="mgr-user-cards">
        <table>
          <thead>
            <tr>
              <th></th>
              <th>User ID</th>
              <th>Email</th>
              <th>Gender</th>
              <th>License</th>
              <th>Delete</th>
            </tr>
          </thead>
          <tbody>

            <?php
              if($_POST['delete']!==NULL)
              {
                $target_id = $_POST['delete'];
                echo "<script>alert('$target_id')</script>";
                $sql = "delete from user where u_id='$target_id'";
                $rst = mysqli_query($conn, $sql);
              }
            ?>
            <?php
            if(!isset($_POST['user-search-text'])||(isset($_POST['user-search-text'])&&$_POST['user-search-text']=='')){
              $sql = "select * from user order by u_id asc";
              $rst = mysqli_query($conn, $sql);
              for($i = 0; $user = mysqli_fetch_assoc($rst);$i++) {?>
              <tr>
                <td><?php echo $i; ?></td>
                <td><?php echo $user['u_id']; ?></td>
                <td><?php echo $user['email']; ?></td>
                <td><?php echo $user['gender']; ?></td>
                <td><?php echo $user['license']; ?></td>
                <td>
                  <form method="post" action='mgr_user.php'>
                    <input id="fake" type="text" name="user-search-text" value="">
                    <input type="submit" name="delete" value="<?php echo $user['u_id']; ?>">
                  </form>
                </td>
                </tr>
           <?php }
          } else {
             $target_id = trim($_POST['user-search-text']);
             $sql_target = "select * from user where u_id = '$target_id'";
             $rst_target = mysqli_query($conn, $sql_target);
             $target_user = mysqli_fetch_assoc($rst_target);
             ?>
                 <tr>
                   <td><?php echo '1'; ?></td>
                   <td><?php echo $target_user['u_id']; ?></td>
                   <td><?php echo $target_user['email']; ?></td>
                   <td><?php echo $target_user['gender']; ?></td>
                   <td><?php echo $target_user['license']; ?></td>
                   <td>
                     <form method="post" action='mgr_user.php'>
                       <input id="fake" type="text" name="user-search-text" value="">
                       <input type="submit" name="delete" value="<?php echo $target_user['u_id']; ?>">
                     </form>
                   </td>
              </tr>
            <?php }?>
          </tbody>
        </table>
        <?php mysqli_close($conn); ?>
      </div>
    </div>
  </body>
</html>
