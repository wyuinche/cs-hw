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
    <title>
      Sign Up
    </title>
  </head>
  <body>
    <div class="register-header">
      <h1>
        Sign Up
      </h1>
    </div>
    <div class="register-section">
      <form class="register-form" action="register.php" method="post">
        <table>
          <tr>
            <td>User ID</td>
            <td><input type="text" name="new-id" value="ID"></td>
          </tr>
          <tr>
            <td>Password</td>
            <td><input type="password" name="new-pw" value="pw"> </td>
          </tr>
          <tr>
            <td>Email</td>
            <td><input type="text" name="new-email" value="email"> </td>
          </tr>
          <tr>
            <td>Gender</td>
            <td>
              <input id="gender" type="checkbox" name="new-male" value="male" onclick="checking(this);"> Male <br>
              <input id="gender" type="checkbox" name="new-female" value="female" onclick="checking(this);">Female <br>
            </td>
          </tr>
        </table>
        <input type="submit" name="submit" value="ok">
      </form>
    </div>
    <script type="text/javascript">
      function checking(x) {
        let box = document.getElementsById("gender");
        for(let i=0; i<box.length; i++){
          if(box[i] != x){
              box[i].checked = false;
            }
          }
        };
    </script>
  </body>
</html>
