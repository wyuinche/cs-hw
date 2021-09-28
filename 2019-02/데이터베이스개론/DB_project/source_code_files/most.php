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
<?php include('dbconn.php');

  $user_id = $_SESSION['ss_user_id'];
  $music_id = $_POST['most-music-id'];

  $sql = "update like_list set count=1 where u_id='$user_id' and m_id='$music_id'";
  $rst = mysqli_query($conn, $sql);

  echo "<script>alert('included to most like list');</script>";
  echo "<script>location.replace('mypage.php');</script>";
?>
