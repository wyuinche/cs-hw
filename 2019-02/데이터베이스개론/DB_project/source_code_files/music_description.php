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
<?php include("dbconn.php"); ?>

<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title>
      MUSIC
    </title>
  </head>
  <body>
    <?php
      $music_id = $_POST['music-id'];
      $sql = "select v.a_title, m.m_title, v.artist_name, m.composer, m.lyricist, v.r_date, v.genre
      from music m, (select a_id, a_title, artist_name, r_date, genre from artist, album where album.artist_id=artist.artist_id) v where m.a_id=v.a_id and m.m_id='$music_id'";
      $rst = mysqli_query($conn, $sql);
      $music = mysqli_fetch_assoc($rst);
    ?>
    <button id='musiclist' type="button" name="button"><a href="music_main.php">Music List</a></button>

    <div class="music-info">
      <div class="music-cover">
        <?php echo"<img src='$music_id.jpg'/>" ?>
      </div>
      <div class="music-des">
        <h1><?php echo $music['m_title']; ?></h1>
        <table id='table2'>
              <tr>
                <td>Album</td>
                <td><?php echo $music['a_title']; ?></td>
              </tr>
              <tr>
                <td>Artist</td>
                <td><?php echo $music['artist_name']; ?></td>
              </tr>
              <tr>
                <td>Composer</td>
                <td><?php echo $music['composer']; ?></td>
              </tr>
              <tr>
                <td>Lyricist</td>
                <td><?php echo $music['lyricist']; ?></td>
              </tr>
              <tr>
                <td>Released Date</td>
                <td><?php echo $music['r_date']; ?></td>
              </tr>
              <tr>
                <td>Genre</td>
                <td><?php echo $music['genre']; ?></td>
              </tr>
        </table>
      </div>
      <div class="lyrics">
        <?php
          $fp = fopen("$music_id.txt", "r") or die("file open fail");
          while( !feof($fp) ) {
            echo fgets($fp);
          }
          fclose($fp);
        ?>
      </div>
    </div>
    <?php mysqli_close($conn); ?>
  </body>
</html>
