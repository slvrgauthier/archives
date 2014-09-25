$().ready(function() {
    $.getJSON('chanteurs.json', function(data){
        $.each(data, function(entryIndex, entry) {
            var html = "<li class='horizontal'>"+entry['nom']+"<img id='"+entry['nom_reel']+"' src='"+entry['image']+"'/><ul id='albums_"+entry['nom_reel']+"'></ul></li>";
            $("#catalogue").append(html);
        });
        $('img').click(function(){
            $('img').toggle(function() {
                var id = $(this).attr('id');
                var idListe = $(this).attr('id');
                $(idListe).empty();
                $.getJSON($(this)['nom']+'.json', function(data) {
                    $.each(data, function(entryIndex, entry) {
                        var html = "<li>"+entry['nom']+"<ul/>"+"</li>";
                        $(idListe).append(html);
                    });
            });
            },
            function() {
                var idListe = $(this).attr('id');
                $(idListe).empty(); 
            }
            );
        });
    });
});
