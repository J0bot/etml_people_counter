<?php
    require('./src/php/Application/DBHelper.php');

    $database = new DBHelper;
    //echo(password_hash(1234, PASSWORD_BCRYPT));

    $database->deleteAllRecord();
   
    

    header("Location: /");
?>