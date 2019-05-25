$(document).ready(function () {
    send_data_url();
    $(".black-friday-banner .close-banner").click(function () {
        $('.black-friday-banner').hide();
    });
    // DESKTOP FEATURES TABS
    $(".features-tabs_item").on('click', function () {
        var i = $(this).data('nav');
        var $tab = $('.features-content[data-tab = "' + i + '"]');
        $(this).toggleClass("active");
        $(".features-tabs_item").not(this).removeClass("active");
        $(".features-content").removeClass("active");
        $tab.addClass("active");
    });
     $('.user-exit').click(function () {
        if ($(this).data('chat') && $(this).data('chat') == 1) {
            Intercom('shutdown');
        }
    });
    $(".main_select").click(function () {
        customOptionsBlock = $(this).find("ul.select_options");
        if (customOptionsBlock.hasClass('act')) {
            customOptionsBlock.hide();
        } else {
            customOptionsBlock.show();
        }
        customOptionsBlock.toggleClass('act');
    });
    $(".main_select ul.select_options li").click(function () {
        $(this).parent().find(' li').removeClass('active');
        $(this).addClass('active');
        $(this).parent().parent().find('.sel-opt').text($(this).text());
        $(this).parent().parent().find("input[type='hidden']").val($(this).attr("data-value"));
    });
    $(document).mouseup(function (e) {
        var div = $("ul.select_options li");
        if (!div.is(e.target)
                && div.has(e.target).length === 0) {
            $("ul.select_options").hide();
        }
    });
    $('.min').click(function () {
        var min = $(this).parent().find('.count');
        if (parseInt(min.text()) > $(this).data('min')) {
            var count = parseInt(min.text()) - 1;
            min.text(count);
            $(this).parent().find('input').val(count);
        }
    });
    $('.max').click(function () {
        var max = $(this).parent().find('.count');
        if (parseInt(max.text()) < $(this).data('max')) {
            var count = parseInt(max.text()) + 1;
            max.text(count);
            $(this).parent().find('input').val(count);
        }
    });
    $('#place_order_home').on('click change keypress keyup', function (event) {
        place_calcul(0);
    });
    $('#place_order2').on('click change keypress keyup', function (event) {
        place_calcul(2);
    });
    $('#em_us_place_order').click(function () {
        $('#em_us_place_order').removeClass('err-fields');
    });
    $('#em_you_order').click(function () {
        if ($('#em_us_place_order').val() == '') {
            $('#em_us_place_order').addClass('err-fields');
            return false;
        }
        $('#em_pl_form').submit();
    });
    if ($('.reviews_items-wrp').length > 0) {
        $.post(window.location.origin + "/api_member/view_reviews", {'reviews-customers': 1}, function (responce) {
            if (responce != '') {
                $('.reviews_items-wrp').html(responce);
            }
            if (window.screen.width < 650) {
                $(".review_item").removeClass('hiddenitem');
            }
        });
        $('body').on('click', '.more-reviews', function () {
            if ($('.reviews_items-wrp .hiddenitem').length <= 3) {
                $('.more-reviews').hide();
            }
            $('.reviews_items-wrp .hiddenitem:lt(3)').fadeIn().removeClass('hiddenitem');
        });
    }
    $('.user-btn-mob,.mob-login').click(function () {
        window.location.href = '/login';
    });
    $('.cc_close_info,.action-info-btn,.cc_info .btn_term,.cc_close_info a').click(function () {
        $('.cc_info').hide();
        var data ={};
        $.post(window.location.origin + "/api_member/info_cookie_close", data, function (responce) { });
        return true;
    });
    $('.login_close,.close-forgot').click(function () {
        $('#login-popup,.txt_forgot_send,.close-forgot').hide();
    });
    $("#login_popup_btn").click(function () {
        var email = $('#login_mail').val().trim();
        var pass = $('#login_pass').val().trim();
        if (!/^([\w-]+(?:\.[\w-]+)*)@((?:[\w-]+\.)*\w[\w-]{0,66})\.([a-z]{2,4}(?:\.[a-z]{2})?)$/i.test(email) || email == '') {
            $('#login_mail').addClass('err-input');
            return false;
        }
        if (pass == '') {
            $("#login_pass").addClass('err-input');
            return false;
        }
        var data = {email: email, password: pass};
        $(this).hide();
        $('.loader-acc').show();
        $.post(window.location.origin + "/check_email", data, function (responce) {
            if (responce) {
                if (parseInt(responce) > 0) {
                    $('.user-btn').hide();
                    $('.user-signed').show();
                    $('#form_login').submit();
                } else {
                    $("#login_popup_btn").show();
                    $('#login_mail').css('color', 'red');
                    $('#login_pass').css('color', 'red');
                }
            } else {
                $("#login_popup_btn").show();
            }
            $('.loader-acc').hide();
        });
        return false;
    });
    $("#login_pass,#login_mail").click(function () {
        $("#login_pass,#login_mail").removeClass('err-input');
    });
    $("#login_pass,#login_mail").click(function () {
        $("#login_pass,#login_mail").removeClass('err-input');
    });
    $("#login_forget").click(function () {
        $(".login_inner").hide();
        $('#login_mail_forgot,#forget_btn,#login_back,#forget_btn,.forgot_inner').show();
    });
    $("#login_back").click(function () {
        $(".login_inner").show();
        $(".forgot_inner").hide();
    });
    $("#new_password, #new_password_confirm").click(function () {
        $("#new_password, #new_password_confirm").removeClass('err-input');
    });
    $("#new_change_password").click(function () {
        if (($("#new_password").val() != $("#new_password_confirm").val()) || $("#new_password").val() == '' || $("#new_password_confirm").val() == '') {
            $("#new_password, #new_password_confirm").addClass('err-input');
            return false;
        }
    });
    $("#forget_btn").click(function () {
        var email = $('#login_mail_forgot').val();
        if (!/^([\w-]+(?:\.[\w-]+)*)@((?:[\w-]+\.)*\w[\w-]{0,66})\.([a-z]{2,4}(?:\.[a-z]{2})?)$/i.test(email) || email == '') {
            $('#login_mail_forgot').addClass('err-input');
            return false;
        }
        var data = {email: email};
        $('#forget_btn,#login_back,#forget_btn').hide();
        $('.loader-forgot').show();
        $.post(window.location.origin + "/forgot", data, function (responce) {
            if (responce) {
                if (responce == 1) {
                    $('#login_mail_forgot,.loader-forgot').hide();
                    $('#login_mail_forgot').val('');
                    $('.txt_forgot_send').text('We sent you a notification, please check your email!').show();
                    $('.close-forgot').show();
                    setTimeout(function () {
                        $('.close-forgot').click();
                    }, 4000);
                } else {
                    alert('Error Email');
                }
            } else {
                $('#forget_btn,#login_back,#forget_btn').show();
                alert('Error Request');
            }
            $('.loader-forgot').hide();
        });
        return false;
    });


});
var ac_level_hs = {
    '10800': 30.00,'28800': 24.00, '86400': 19.00, '172800': 16.00, '259200': 15.00, '432000': 14.00, '604800': 13.00, '864000': 11.00, '1209600': 9.00
};
var ac_level_rs = {
    '10800': 35.00,'28800': 26.00, '86400': 20.00, '172800': 17.00, '259200': 16.00, '432000': 15.00, '604800': 14.00, '864000': 12.00, '1209600': 10.00
};
var ac_level_un = {
    '10800': 39.00,'28800': 29.00, '86400': 21.00, '172800': 18.00, '259200': 17.00, '432000': 16.00, '604800': 15.00, '864000': 13.00, '1209600': 11.00
};
var ac_level_ms = {
    '10800': 49.00,'28800': 41.00, '86400': 29.00, '172800': 26.00, '259200': 24.00, '432000': 22.00, '604800': 20.00, '864000': 17.00, '1209600': 14.00
};
var ac_level_ph = {
    '10800': 59.00,'28800': 48.00, '86400': 40.00, '172800': 34.00, '259200': 30.00, '432000': 29.00, '604800': 27.00, '864000': 23.00, '1209600': 19.00
};

function place_calcul(tp) {
    var tp = (tp > 0) ? tp : '';
    var ac_level = $("#academic_level" + tp).val();
    var deadline = $("#place_ddl" + tp).val();
    if (ac_level == '1') {
        var currentPagePrice = ac_level_hs[deadline]
    }
    if (ac_level == '2') {
        var currentPagePrice = ac_level_rs[deadline];
    }
    if (ac_level == '3') {
        var currentPagePrice = ac_level_un[deadline]
    }
    if (ac_level == '4') {
        var currentPagePrice = ac_level_ms[deadline]
    }
    if (ac_level == '5') {
        var currentPagePrice = ac_level_ph[deadline]
    }
    var pagesNum = $('#place_pages' + tp).val();
    var total = pagesNum * currentPagePrice;
    $('#price' + tp).text('$' + total);
}

function send_data_url(){
     var data = {'url_site': window.location.href, 'url_referrer': document.referrer};
     $.post(window.location.origin + "/api_url/send_url_data", data, function (responce) { });
}

// AUTO SCROLL NUMBERS
var a = 0;
$(window).scroll(function () {
    var oTop = $("#counter").offset().top - window.innerHeight;
    if (a == 0 && $(window).scrollTop() > oTop) {
        $(".counter-value").each(function () {
            var $this = $(this),
                    countTo = $this.attr("data-count");
            $({
                countNum: $this.text()
            }).animate({
                countNum: countTo
            },
                    {
                        duration: 1500,
                        easing: "swing",
                        step: function () {
                            $this.text(Math.floor(this.countNum));
                        },
                        complete: function () {
                            $this.text(this.countNum);
                            //alert(‘finished’);
                        }
                    });
        });
        a = 1;
    }
});
slider_init_rev('.reviews_items-wrp');
slide_init('.samples_items-wrp');
// MOBILE MENU
$(".mob-menu-btn").click(function () {
    $(".main-menu").toggleClass("active");
});
// SLIDER
$(".review-slider-btn").click(function () {
    var cur = parseInt($('.review_item.active').data('item'));
    var step = ($(this).hasClass('next')) ? cur + 1 : cur - 1;
    console.log(step);
    if ($(".review_item[data-item='" + step + "']").length) {
        slider_show(step);
        $(".review_item[data-item='" + cur + "']").removeClass('active');
        $(".review_item[data-item='" + step + "']").addClass('active');
    }
});

function slider_show(step) { // slider function
    var sl_width = $(".review_item[data-item='" + step + "']").outerWidth(true) * 1;
    console.log(sl_width);
    $('.reviews_items-wrp').animate({marginLeft: "-" + sl_width * step}, 50);
}
function slider_init_rev(obj) { // slider function
    $(obj).find(".review_item").each(function () {
        $(this).attr('data-item', $(this).index());
    });
}
// SAMPLES SLIDER
$(".samples-slider-btn").click(function () {
    var cur = parseInt($('.samples_item.active').data('item'));
    var step = ($(this).hasClass('next')) ? cur + 1 : cur - 1;
    console.log(step);
    if ($(".samples_item[data-item='" + step + "']").length) {
        slide_show(step);
        $(".samples_item[data-item='" + cur + "']").removeClass('active');
        $(".samples_item[data-item='" + step + "']").addClass('active');
    }
});

function slide_show(step) { // slider function
    var slider_width = $(".samples_item[data-item='" + step + "']").outerWidth(true) * 1;
    console.log(slider_width);
    $('.samples_items-wrp').animate({marginLeft: "-" + slider_width * step}, 50);
}
function slide_init(obj) { // slider function
    $(obj).find(".samples_item").each(function () {
        $(this).attr('data-item', $(this).index());
    });
}
function getCookie(name) {
    var matches = document.cookie.match(new RegExp(
            "(?:^|; )" + name.replace(/([\.$?*|{}\(\)\[\]\\\/\+^])/g, '\\$1') + "=([^;]*)"
            ));
    return matches ? decodeURIComponent(matches[1]) : undefined;
}
