$(function () {
    var _pageNum = 1;
    var _pageSize = 5;
    var urlFindName = "/admin/findUsername";
    var urlChange = "/admin/changeStatus";

    // 根据用户名、页面索引、页面大小获取用户列表
    function getUserList(pageNum, pageSize) {
        $.ajax({
            url: urlFindName,
            type: "GET",
            contentType: "application/json",
            data: {
                "pageNum": pageNum,
                "pageSize": pageSize,
                "username": $(".searchUsername").val()
            },
            success: function (data) {
                var prefix = data.toString().substring(0, 4);
                if(prefix == '<div'){
                    $("#userList").html(data);
                }
            }
        });
    }

    // 搜索
    $(".searchUsernameBtn").click(function () {
        getUserList(1, _pageSize);
    });
    //绑定回车键
    $('.searchUsername').bind('keydown', function (event) {
        if (event.keyCode == 13) {
            getUserList(1, _pageSize)
        }
    });

    // 分页
    $.tbpage("#userList", function (pageNum, pageSize) {
        getUserList(pageNum, pageSize)
        _pageNum = pageNum
        _pageSize = pageSize
    });

    var userId;
    var userStatus;
    //监听userList事件子事件，并绑定userStatus事件
    $("#userList").off("click", ".userStatus").on("click", ".userStatus", function () {
        userId = $(this).attr('userId')
        userStatus = $(this).attr('userStatus')
    });
    //不能监听userStatus事件，因为重新加载用户列表之后，新列表没有监听事件
    // $(".userStatus").click(function () {});

    //状态model
    $('#statusModel').on('show.bs.modal', function (event) {
        var button = $(event.relatedTarget) // Button that triggered the modal
        var content = button.data('whatever') // Extract info from data-* attributes
        content = '是否确定' + content + '该用户'
        // modal.find('.modal-body input').val('是否确定' + content + '该用户')
        $(this).find('.modal-body p').text(content)
    });

    $('.modelSubmit').click(function () {
        $.ajax({
            url: urlChange,
            type: "GET",
            contentType: "application/json",
            data: {
                "userId": userId,
                "userStatus": userStatus
            },
            success: function (data) {
                if(data.success){
                    getUserList(_pageNum, _pageSize)
                } else {
                    alert(data.errorMsg)
                }
            }
        });
    });

});