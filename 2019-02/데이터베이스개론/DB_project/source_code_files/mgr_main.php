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
  include("dbconn.php");
?>

<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title>Manager</title>
    <style>
      #fake{
        display:none;
      }
    </style>
  </head>
  <body>
    <div class="mgr-header">
      <div class="mgr-title">
        <h1>Service Manager</h1>
      </div>
      <div class="mgr-nav">
        <?php
          $user_id = $_SESSION['ss_user_id'];
        ?>
        <p>Hello, <?php echo $user_id?></p>
        <button id='mgr-mypage' type="button" name="button"><a href="mypage.php">My Page</a></button>
        <button id='mgr-signout' type="button" name="button"><a href="sign_out.php">Sign Out</a></button>
      </div>
    </div>
    <div class="mgr-select" onclick="user_list_page();">
      <form action="mgr_user.php" method="post">
        <div>
          <input id="fake" type="text" name="user-search-text" value="">
          <input id="fake" type="text" name="delete" value="">
           <input type="submit" name="mgr-main-submit" value="User List">
        </div>
      </form>
      <form action="music_main.php" method="post">
        <div>
          <!-- <input id="fake" type="text" name="user-search-text" value="">
          <input id="fake" type="text" name="delete" value=""> -->
           <input type="submit" name="mgr-main-submit" value="Music List">
        </div>
      </form>
    </div>

    </script>
  </body>
</html>
