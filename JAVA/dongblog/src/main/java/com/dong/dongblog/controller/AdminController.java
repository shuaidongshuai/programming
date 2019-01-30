package com.dong.dongblog.controller;

import com.dong.dongblog.dto.Menu;
import com.dong.dongblog.dto.ResponseCommonDto;
import com.dong.dongblog.dto.ResponseUserListDto;
import com.dong.dongblog.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.ArrayList;
import java.util.List;

@Controller
@RequestMapping("/admin")
public class AdminController {
    @Autowired
    UserService userService;

    @GetMapping("/manager")
    public String manager(Model model) {
        List<Menu> menus = new ArrayList<>();
        menus.add(new Menu("用户管理", "/admin/userList"));
        menus.add(new Menu("文章管理", "/user"));
        model.addAttribute("menus", menus);
        return "/admin/manager";
    }

    @GetMapping("/userList")
    public String page(int pageNum, int pageSize, Model model) {
        ResponseUserListDto responseUserListDto = userService.findList(pageNum, pageSize);
        model.addAttribute("pageInfo", responseUserListDto.getPageInfo());
        model.addAttribute("users", responseUserListDto.getPageInfo().getList());
        return "/user/userList";
    }

    /**
     * 模糊查询
     * @param pageNum
     * @param pageSize
     * @param username
     * @param model
     * @return
     */
    @GetMapping("/findUsername")
    public String findUsername(int pageNum, int pageSize, String username, Model model) {
        ResponseUserListDto responseUserListDto;
        if(username == null || "".equals(username)){
            responseUserListDto = userService.findList(pageNum, pageSize);
        } else {
            responseUserListDto = userService.findListUsernameLike(pageNum, pageSize, username);
        }
        model.addAttribute("pageInfo", responseUserListDto.getPageInfo());
        model.addAttribute("users", responseUserListDto.getPageInfo().getList());
        return "/user/userList :: #userListReplace";
    }

    @GetMapping("/changeStatus")
    @ResponseBody
    public ResponseCommonDto changeStatus(Long userId, String userStatus) {
        ResponseCommonDto responseCommonDto = userService.changeStatus(userId, userStatus);
        return responseCommonDto;
    }

}
