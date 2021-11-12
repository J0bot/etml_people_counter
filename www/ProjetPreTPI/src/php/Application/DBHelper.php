<?php

use function PHPSTORM_META\type;

class DBHelper {
    public $instance;

    private function getInstance() {
        if (!empty($this->instance)) return $this->instance;

        $dsn = "mysql:host=localhost;dbname=db_pretpi;charset=utf8";
        $user = "root";
        $password = "root";

        $this->instance = new PDO($dsn, $user, $password);
        return $this->instance;
    }

    public function getArduinos() {
        $instance = $this->getInstance();

        $query = $instance->prepare("SELECT l.ardMacAddress, r.regName, r.regType FROM linkedto l JOIN t_region r ON (l.regId = r.regId);");
        $query->execute();

        return $query->fetchAll();
    }

    public function getArduinosFromRoomName($regName) {
        $instance = $this->getInstance();

        $query = $instance->prepare("SELECT l.ardMacAddress FROM linkedto l JOIN t_region r ON (r.regId = l.regId) WHERE r.regName = :regName;");
        $query->bindParam('regName', $regName);
        $query->execute();

        return $query->fetchAll();
    }

    public function getRoomDatas($macAddresses) {
        $instance = $this->getInstance();
        $inQuery = implode(',', array_fill(0, count($macAddresses), '?'));

        $query = $instance->prepare("SELECT recDate, recType FROM t_record WHERE ardMacAddress IN (" . $inQuery . ") AND DATE(recDate) = DATE(now());");

        foreach ($macAddresses as $key => $value) {
            $query->bindValue(($key+1), $value);
        }
        $query->execute();

        return $query->fetchAll();
    }

    public function addRecord($recDate, $recType, $ardMacAddress) {
        $instance = $this->getInstance();

        $query = $instance->prepare("INSERT INTO t_record (recDate, recType, ardMacAddress) VALUES (:recDate, :recType, :ardMacAddress); ");
        $query->bindParam('recDate', $recDate);
        $query->bindParam('recType', $recType);
        $query->bindParam('ardMacAddress', $ardMacAddress);

        $query->execute();
    }
}
?>