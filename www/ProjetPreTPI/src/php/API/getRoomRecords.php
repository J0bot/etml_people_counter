<?php
    require('./src/php/Application/DBHelper.php');

    if(!empty($_GET)) {
        $database = new DBHelper();
        echo (json_encode($database->getRoomDatas(json_decode($_GET['macAddress']))));
    } else {
        echo ('no data provided');
    }
?>