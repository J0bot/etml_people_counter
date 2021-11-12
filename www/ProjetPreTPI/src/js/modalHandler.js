function updateModal(roomName) {
    modal = $('#resumeModal');
    modal.modal('show');
    modal.find('.modal-title').text(roomName);

    $.ajax({
        url: './api/getArduinosFromRegionName',
        type: 'GET',
        data: 'regionName=' + roomName,
        success: function(result) {
            roomData = [];
            if (typeof roomData[roomName] == 'undefined') {
                roomData[roomName] = [];
            }

            Object.entries(JSON.parse(result)).forEach(macAddress => {
                roomData[roomName] = roomData[roomName].concat(macAddress[1]['ardMacAddress']);
            });

            Object.entries(roomData).forEach(data => {
                loadOneChart(data, 'modalCanvas', false);
            });
        },
    });

    $('.modal-body').find('.entry').text($(`#${roomName}`).find('.entry').text());
    $('.modal-body').find('.current').text($(`#${roomName}`).find('.current').text());
    $('.modal-body').find('.exit').text($(`#${roomName}`).find('.exit').text());
}