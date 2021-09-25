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

$album = $_POST['new-album'];
$album_n = $_POST['new-album-n'];
$song = $_POST['new-song'];
$artist = $_POST['new-artist'];
$artist_n = $_POST['new-artist-n'];
$composer = $_POST['new-composer'];
$lyricist = $_POST['new-lyricist'];
$date = $_POST['new-date'];
$genre = $_POST['new-genre'];

$sql_m_id= "select * from music";
$rst_m_id = mysqli_query($conn, $sql_m_id);
$m_id_new = 1 + mysqli_num_rows($rst_m_id);

if(!$album||!$song||!$artist||!$composer||!$lyricist||!$date||!$genre)
{
  echo "<script>alert('fill the blankds');</script>";
  echo "<script>location.replace('add_music.php');</script>";
}

// exist artist
$sql_artist = "select * from artist where artist_id='$artist_n'";
$rst_artist = mysqli_query($conn, $sql_artist);
$artist_exist = mysqli_num_rows($rst_artist);

if($artist_exist!=0)
{
  $sql_album = "select * from music where a_id='$album_n'";
  $rst_album = mysqli_query($conn, $sql_album);
  $album_exist = mysqli_num_rows($rst_album);
  if($album_exist !=0)
  {
    $m_order = 1 + $album_exist;
     //insert
     $sql = "insert into music values('$m_id_new', '$album_n', '$song', '$composer', '$m_order', '$lyricist')";
     $rst = mysqli_query($conn, $sql);
  }
  else {
    $sql_album_r = "select * from album";
    $rst_album_r = mysqli_query($conn, $sql_album_r);
    $a_id_new = 1 + mysqli_num_rows($rst_album_r);

    $sql2 = "insert into album values('$a_id_new', '$album', '$artist_n', '$date', '$genre')";
    $rst2 = mysqli_query($conn, $sql2);

    $sql3 = "insert into music values('$m_id_new', '$a_id_new', '$song', '$composer', '1', '$lyricist')";
    $rst3 = mysqli_query($conn, $sql3);
  }
}
else {
  $sql_artist_r = "select * from artist";
  $rst_artist_r = mysqli_query($conn, $sql_artist_r);
  $artist_id_new = 1 + mysqli_num_rows($rst_artist_r);

  $sql_album_r = "select * from album";
  $rst_album_r = mysqli_query($conn, $sql_album_r);
  $a_id_new = 1 + mysqli_num_rows($rst_album_r);

  $sql4 = "insert into artist values('$artist_id_new', '$artist')";
  $rst4 = mysqli_query($conn, $sql4);

  $sql2 = "insert into album values('$a_id_new', '$album', '$artist_id_new', '$date', '$genre')";
  $rst2 = mysqli_query($conn, $sql2);

  $sql3 = "insert into music values('$m_id_new', '$a_id_new', '$song', '$composer', '1', '$lyricist')";
  $rst3 = mysqli_query($conn, $sql3);
}

echo "<script>location.replace('music_main.php')</script>";

?>
