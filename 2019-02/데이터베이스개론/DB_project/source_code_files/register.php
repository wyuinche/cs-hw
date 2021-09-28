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

$will_id = trim($_POST['new-id']);
$will_pw = trim($_POST['new-pw']);
$will_em = trim($_POST['new-email']);
$will_ma = trim($_POST['new-male']);
$will_fe = trim($_POST['new-female']);

if(!$will_id||!$will_pw||!$will_em||(!$will_ma&&!$will_fe)){
  echo "<script>alert('Please fill in the blanks');</script>";
  echo "<script>location.replace('sign_up.php');</script>;";
  exit;
}

if($will_ma){
  $sql_new = "insert into user values ('$will_id', '$will_pw', '$will_em', '$will_ma', 'general')";
}
else if($will_fe){
  $sql_new = "insert into user values ('$will_id', '$will_pw', '$will_em', '$will_fe', 'general')";
}
$rst = mysqli_query($conn, $sql_new);

echo "<script>alert('sign up')</script>";
echo "<script>location.replace('login.php')</script>";
