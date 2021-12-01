<?php
    require('./src/php/Application/DBHelper.php');

    $database = new DBHelper;
    
    //Password authentification
    
    

    if ($userPass == $password) {
        $database->deleteAllRecord();
    }


    header("Location: /");
?>