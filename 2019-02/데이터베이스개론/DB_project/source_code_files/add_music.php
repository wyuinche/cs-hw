/*
Copyright (C) 2019  Oracle Corporation and/or its affiliates

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
    <title>Add Music</title>
  </head>
  <body>
    <div class="add-header">
        <div class="add-title">
          <h1>Add Music</h1>
        </div>
        <div class="music-nav">
          <?php
            $user_id = $_SESSION['ss_user_id'];
          ?>
          <p>Hello, <?php echo $user_id?></p>
          <button id='mypage' type="button" name="button"><a href="mypage.php">My Page</a></button>
          <button id='signout' type="button" name="button"><a href="sign_out.php">Sign Out</a></button>
          <button id='musiclist' type="button" name="button"><a href="music_main.php">Music List</a></button>

        </div>
    </div>
    <div class="add-section">
      <form class="add-form" action="add.php" method="post">
        <table>
          <tr>
            <td>Album Title</td>
            <td><input type="text" name="new-album" value=""></td>
          </tr>
          <tr>
            <td>Album Number</td>
            <td><input type="text" name="new-album-n" value=""></td>
          </tr>
          <tr>
            <td>Song Title</td>
            <td><input type="text" name="new-song" value=""> </td>
          </tr>
          <tr>
            <td>Artist</td>
            <td><input type="text" name="new-artist" value=""> </td>
          </tr>
          <tr>
            <td>Artist Number</td>
            <td><input type="text" name="new-artist-n" value=""></td>
          </tr>
          <tr>
            <td>Composer</td>
            <td><input type="text" name="new-composer" value=""> </td>
          </tr>
          <tr>
            <td>Lyricist</td>
            <td><input type="text" name="new-lyricist" value=""> </td>
          </tr>
          <tr>
            <td>Released Date</td>
            <td><input type="text" name="new-date" value=""> </td>
          </tr>
          <tr>
            <td>Genre</td>
            <td><input type="text" name="new-genre" value=""> </td>
          </tr>
        </table>
        <input type="submit" name="submit" value="ok">
      </form>
    </div>
    <?php mysqli_close($conn); ?>
  </body>
</html>
