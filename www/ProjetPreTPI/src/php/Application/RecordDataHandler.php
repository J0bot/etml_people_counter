<?php 

class RecordDataHandler {
    public function extractEntriesCount($recordDatas) {
        return count(array_filter($recordDatas, function ($currentArray) {
            return $currentArray['recType'] === 'entry';
        }));
    }
    
    public function extractExitsCount($recordDatas) {
        return count(array_filter($recordDatas, function ($currentArray) {
            return $currentArray['recType'] === 'exit';
        }));
    }

    public function extractCurrentsCount($recordDatas) {
        return $this->extractEntriesCount($recordDatas) - $this->extractExitsCount($recordDatas);
    }
}
?>