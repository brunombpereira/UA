$(document).ready(function(){
    
    $('.search-toggle').click(function(){
        $('.search-wrapper').toggleClass('show');
    });

    $('.modal-toggle').click(function(){
        $('.modalBox').toggleClass('show');
    })

    $('.modalBox').click(function(){
        $(this).removeClass('show');
    });

    $('.spinner').click(function(){
        $(".theme-selector").toggleClass('show');
    });
    $('.light').click(function(){
        $('body').addClass('light-theme');
        $('body').removeClass('dark-theme');
    });
    $('.dark').click(function(){
        $('body').toggleClass('dark-theme');
        $('body').removeClass('light-theme');
    });
});



// smooth scroll
$(document).ready(function(){
    $(".navbar .nav-link").on('click', function(event) {

        if (this.hash !== "") {

            event.preventDefault();

            var hash = this.hash;

            $('html, body').animate({
                scrollTop: $(hash).offset().top
            }, 700, function(){
                window.location.hash = hash;
            });
        } 
    });
}); 

$(window).on("load", function() {
    var t = $(".portfolio-container");
    t.isotope({
        filter: ".new",
        animationOptions: {
            duration: 750,
            easing: "linear",
            queue: !1
        }
    }), $(".filters a").click(function() {
        $(".filters .active").removeClass("active"), $(this).addClass("active");
        var i = $(this).attr("data-filter");
        return t.isotope({
            filter: i,
            animationOptions: {
                duration: 750,
                easing: "linear",
                queue: !1
            }
        }), !1
    })
})

$('#nav-toggle').click(function(){
    $(this).toggleClass('is-active')
    $('ul.nav').toggleClass('show');
});




$("#animate-button-1").click(function(){
    $("#título-1").animate({
        opacity: 0
    }, 1000);
    $("#texto-1").animate({
        opacity: 0
    }, 1000, function(){
        $("#título-1").hide();
        $("#texto-1").hide();
        $("#animate-button-1").hide();
        $("#animate-button-2").show();
        $("#animate-button-3").show();
        $("#título-2").show().animate({
            opacity: 1
        }, 1000);
        $("#texto-2").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-2").click(function(){
    $("#título-2").animate({
        opacity: 0
    }, 1000);
    $("#texto-2").animate({
        opacity: 0
    }, 1000, function(){
        $("#título-2").hide();
        $("#texto-2").hide();
        $("#animate-button-2").hide();
        $("#animate-button-3").hide();
        $("#animate-button-4").show();
        $("#animate-button-5").show();
        $("#título-3").show().animate({
            opacity: 1
        }, 1000);
        $("#texto-3").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-4").click(function(){
    $("#texto-3").animate({
        opacity: 0
    }, 1000, function(){
        $("#texto-3").hide()
        $("#animate-button-4").hide();
        $("#animate-button-5").hide();
        $("#animate-button-6").show();
        $("#animate-button-7").show();
        $("#texto-4").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-6").click(function(){
    $("#texto-4").animate({
        opacity: 0
    }, 1000, function(){
        $("#texto-4").hide()
        $("#animate-button-6").hide();
        $("#animate-button-7").hide();
        $("#animate-button-8").show();
        $("#animate-button-9").show();
        $("#texto-5").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-8").click(function(){
    $("#título-3").animate({
        opacity: 0
    }, 1000);
    $("#texto-5").animate({
        opacity: 0
    }, 1000, function(){
        $("#título-3").hide()
        $("#texto-5").hide()
        $("#animate-button-8").hide();
        $("#animate-button-9").hide();
        $("#animate-button-10").show();
        $("#título-4").show().animate({
            opacity: 1
        }, 1000);
        $("#texto-6").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-10").click(function(){
    $("#título-4").animate({
        opacity: 0
    }, 1000);
    $("#texto-6").animate({
        opacity: 0
    }, 1000, function(){
        $("#título-4").hide()
        $("#texto-6").hide()
        $("#animate-button-10").hide();
        $("#animate-button-8").show();
        $("#animate-button-9").show();
        $("#título-3").show().animate({
            opacity: 1
        }, 1000);
        $("#texto-5").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-9").click(function(){
    $("#texto-5").animate({
        opacity: 0
    }, 1000, function(){
        $("#texto-5").hide()
        $("#animate-button-8").hide();
        $("#animate-button-9").hide();
        $("#animate-button-6").show();
        $("#animate-button-7").show();
        $("#texto-4").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-7").click(function(){
    $("#texto-4").animate({
        opacity: 0
    }, 1000, function(){
        $("#texto-4").hide()
        $("#animate-button-6").hide();
        $("#animate-button-7").hide();
        $("#animate-button-5").show();
        $("#animate-button-6").show();
        $("#texto-3").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-5").click(function(){
    $("#título-3").animate({
        opacity: 0
    }, 1000);
    $("#texto-3").animate({
        opacity: 0
    }, 1000, function(){
        $("#título-3").hide()
        $("#texto-3").hide()
        $("#animate-button-5").hide();
        $("#animate-button-6").hide();
        $("#animate-button-3").show();
        $("#animate-button-4").show();
        $("#título-2").show().animate({
            opacity: 1
        }, 1000);
        $("#texto-2").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-3").click(function(){
    $("#título-2").animate({
        opacity: 0
    }, 1000);
    $("#texto-2").animate({
        opacity: 0
    }, 1000, function(){
        $("#título-2").hide()
        $("#texto-2").hide()
        $("#animate-button-2").hide();
        $("#animate-button-3").hide();
        $("#animate-button-1").show();
        $("#título-1").show().animate({
            opacity: 1
        }, 1000);
        $("#texto-1").show().animate({
            opacity: 1
        }, 1000);
    });
});















$("#animate-button-1-1").click(function(){
    $("#texto-1-1").animate({
        opacity: 0
    }, 1000, function(){
        $("#texto-1-1").hide()
        $("#animate-button-1-1").hide();
        $("#animate-button-2-2").show();
        $("#animate-button-3-3").show();
        $("#texto-2-2").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-2-2").click(function(){
    $("#título-1-1").animate({
        opacity: 0
    }, 1000);
    $("#texto-2-2").animate({
        opacity: 0
    }, 1000, function(){
        $("#título-1-1").hide();
        $("#texto-2-2").hide();
        $("#animate-button-2-2").hide();
        $("#animate-button-3-3").hide();
        $("#animate-button-4-4").show();
        $("#animate-button-5-5").show();
        $("#título-2-2").show().animate({
            opacity: 1
        }, 1000);
        $("#texto-3-3").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-4-4").click(function(){
    $("#texto-3-3").animate({
        opacity: 0
    }, 1000, function(){
        $("#texto-3-3").hide()
        $("#animate-button-4-4").hide();
        $("#animate-button-5-5").hide();
        $("#animate-button-6-6").show();
        $("#animate-button-7-7").show();
        $("#texto-4-4").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-7-7").click(function(){
    $("#texto-4-4").animate({
        opacity: 0
    }, 1000, function(){
        $("#texto-4-4").hide()
        $("#animate-button-6-6").hide();
        $("#animate-button-7-7").hide();
        $("#animate-button-8-8").show();
        $("#animate-button-9-9").show();
        $("#texto-5-5").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-9-9").click(function(){
    $("#título-2-2").animate({
        opacity: 0
    }, 1000);
    $("#texto-5-5").animate({
        opacity: 0
    }, 1000, function(){
        $("#título-2-2").hide()
        $("#texto-5-5").hide()
        $("#animate-button-8-8").hide();
        $("#animate-button-9-9").hide();
        $("#animate-button-10-10").show();
        $("#título-3-3").show().animate({
            opacity: 1
        }, 1000);
        $("#texto-6-6").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-10-10").click(function(){
    $("#título-3-3").animate({
        opacity: 0
    }, 1000);
    $("#texto-6-6").animate({
        opacity: 0
    }, 1000, function(){
        $("#título-3-3").hide()
        $("#texto-6-6").hide()
        $("#animate-button-8-8").show();
        $("#animate-button-9-9").show();
        $("#animate-button-10-10").hide();
        $("#título-2-2").show().animate({
            opacity: 1
        }, 1000);
        $("#texto-5-5").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-8-8").click(function(){
    $("#texto-5-5").animate({
        opacity: 0
    }, 1000, function(){
        $("#texto-5-5").hide()
        $("#animate-button-6-6").show();
        $("#animate-button-7-7").show();
        $("#animate-button-8-8").hide();
        $("#animate-button-9-9").hide();
        $("#texto-4-4").show().animate({
            opacity: 1
        }, 1000);
    });
});


$("#animate-button-6-6").click(function(){
    $("#texto-4-4").animate({
        opacity: 0
    }, 1000, function(){
        $("#texto-4-4").hide()
        $("#animate-button-6-6").hide();
        $("#animate-button-7-7").hide();
        $("#animate-button-5-5").show();
        $("#animate-button-4-4").show();
        $("#texto-3-3").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-5-5").click(function(){
    $("#título-2-2").animate({
        opacity: 0
    }, 1000);
    $("#texto-3-3").animate({
        opacity: 0
    }, 1000, function(){
        $("#título-2-2").hide()
        $("#texto-3-3").hide()
        $("#animate-button-4-4").hide();
        $("#animate-button-5-5").hide();
        $("#animate-button-2-2").show();
        $("#animate-button-3-3").show();
        $("#título-1-1").show().animate({
            opacity: 1
        }, 1000);
        $("#texto-2-2").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-3-3").click(function(){
    $("#texto-2-2").animate({
        opacity: 0
    }, 1000, function(){
        $("#texto-2-2").hide()
        $("#animate-button-2-2").hide();
        $("#animate-button-3-3").hide();
        $("#animate-button-1-1").show();
        $("#texto-1-1").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-1-1-1").click(function(){
    $("#texto-1-1-1").animate({
        opacity: 0
    }, 1000, function(){
        $("#texto-1-1-1").hide()
        $("#animate-button-1-1-1").hide();
        $("#animate-button-2-2-2").show();
        $("#texto-2-2-2").show().animate({
            opacity: 1
        }, 1000);
    });
});

$("#animate-button-2-2-2").click(function(){
    $("#texto-2-2-2").animate({
        opacity: 0
    }, 1000, function(){
        $("#texto-2-2-2").hide()
        $("#animate-button-1-1-1").show();
        $("#animate-button-2-2-2").hide();
        $("#texto-1-1-1").show().animate({
            opacity: 1
        }, 1000);
    });
});