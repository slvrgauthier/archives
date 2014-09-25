$().ready(function(){
	$('.aime_mess').click(function(){
		var id_mess=$(this).attr('id').replace('mess_', '');
		location.href='../likes/like_tmp.php?id_mess_qu_on_a_like='+id_mess;
	});
	$('.aime_pas_mess').click(function(){
		var id_mess=$(this).attr('id').replace('mess_', '');
		location.href='../likes/dislike_tmp.php?id_mess_qu_on_a_dislike='+id_mess;		
	});
});