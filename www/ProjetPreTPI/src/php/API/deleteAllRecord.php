<?php
    require('./src/php/Application/DBHelper.php');

    $database = new DBHelper;
    $database->deleteAllRecord();

    header("Location: /");
?>