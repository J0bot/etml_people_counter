<?php
    require('./src/php/Application/DBHelper.php');

    if(!empty($_POST['recType']) && !empty($_POST['ardMacAddress'])) {
        $database = new DBHelper;
        $database->addRecord(date("Y-m-d H:i:s.u"), $_POST['recType'], $_POST['ardMacAddress']);
    }
?>