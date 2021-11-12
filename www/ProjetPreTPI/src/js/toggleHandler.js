$(function() {
    $('#toggleCharts').change(function() {
        if(!$(this).prop('checked')) {
            $('.card-body').find('.graphic').each(function(index, element) {
                element.style.display = 'block';
            });
            $('.card-body').find('.counter').each(function(index, element) {
                element.style.display = 'none';
            });

            loadAllCharts();
        } else {
            $('.card-body').find('.counter').each(function(index, element) {
                element.style.display = 'block';
            });
            $('.card-body').find('.graphic').each(function(index, element) {
                element.style.display = 'none';
            });

            initializeCounters();
        }
    });
});