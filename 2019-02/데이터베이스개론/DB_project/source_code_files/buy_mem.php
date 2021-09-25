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

$user_id = $_SESSION['ss_user_id'];
$card_num = $_POST['card-number'];

$sql_exist = "select * from membership where u_id='$user_id'";
$rst_exist = mysqli_query($conn, $sql_exist);
$exist = mysqli_num_rows($rst_exist);

if ($exist != 0)
{
  echo "<script>alert('You already joined in membership');</script>";
  echo "<script>location.replace('music_main.php');</script>";
}
else {
  $sql_card = "insert into membership values('$user_id','$card_num')";
  $rst_card = mysqli_query($conn, $sql_card);
  echo "<script>alert('Start membership');</script>";
  echo "<script>location.replace('music_main.php');</script>";

}
  //insert

?>
