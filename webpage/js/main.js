(function ($) {
// VERTICALLY ALIGN FUNCTION
$.fn.vAlign = function() {
    return this.each(function(i){
    var ah = $(this).height();
    var ph = $(this).parent().height();
    var mh = Math.ceil((ph-ah) / 2);
    $(this).css('padding-top', mh);
    });
};
})(jQuery);
$(document).ready(function(){
	var win_h = $(window).height();
	function setHeight(){
		$('.home > .hero').css({height:win_h});
		$(".vcenter").vAlign();
	}

	setHeight();
	/*$(".slogan h1").slabText({
	        "viewportBreakpoint":300
	});*/
	
	$(window).bind('resize',function() {
		setHeight();
	 });

	 $('#top-nav').onePageNav({

        currentClass: 'current',
        changeHash: false,
        scrollSpeed: 750,
        scrollOffset: 50,
        scrollThreshold: 0.5,
        filter: ':not(.external)',
        begin: function() {
            //I get fired when the animation is starting
        },
        end: function() {
            //I get fired when the animation is ending
        },
        scrollChange: function() {
            //I get fired when you enter a section and I pass the list item of the section
        }
    });

     $('#nav-button').click(function(){
        $top_nav = $('#top-nav');
        if($top_nav.is(':hidden')){
            $top_nav.slideDown("slow");
        }else{
            $top_nav.slideUp();
        }
     })

});