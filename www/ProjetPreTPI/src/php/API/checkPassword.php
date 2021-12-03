<?php
require('./src/php/Application/DBHelper.php');
public function check($password)
{
    $database = new DBHelper;
        

    $database->checkPassword($password);
}



?>