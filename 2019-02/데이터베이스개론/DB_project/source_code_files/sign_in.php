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

$user_id = trim($_POST['login-id']);
$user_pw = trim($_POST['login-password']);

if(!$user_id||!$user_pw){
  echo "<script>alert('Please fill in the blanks');</script>";
  echo "<script>location.replace('login.php');</script>;";
  exit;
}

$sql_us = "select * from user where u_id='$user_id'";
$rst_us = mysqli_query($conn, $sql_us);
$user = mysqli_fetch_assoc($rst_us);

$sql_pw = "select pw from user where u_id='$user_id'";
$rst_pw = mysqli_query($conn, $sql_pw);
$pw = mysqli_fetch_assoc($rst_pw);

if(!$user['u_id']){
  echo "<script>alert('Unregistered ID');</script>";
  echo "<script>location.replace('login.php');</script>";
  exit;
}
else if(!($user_pw === $user['pw'])){
  echo "<script>alert('Wrong Password');</script>";
  echo "<script>location.replace('login.php');</script>";
  exit;
}

$_SESSION['ss_user_id'] = $user_id;

mysqli_close($conn);

if(isset($_SESSION['ss_user_id'])){
  if($user['license']=="general"){
    echo("<script>alert('Welcome User')</script>");
    echo("<script>location.replace('music_main.php');</script>");
  }
  else{
    echo("<script>alert('Welcome Manager')</script>");
    echo("<script>location.replace('mgr_main.php');</script>");
  }
}
?>
