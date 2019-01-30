package com.dong.dongblog.controller;

import com.dong.dongblog.dto.RequestUserDto;
import com.dong.dongblog.model.User;
import com.dong.dongblog.security.AuthUserService;
import com.dong.dongblog.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping
public class HomePageController {
    @Autowired
    UserService userService;

    @Autowired
    AuthUserService authUserService;

    @RequestMapping("/")
    public String index(Model model) {
        User curUser = authUserService.getCurUser();
        model.addAttribute("user", curUser);
        return "/index";
    }

    @GetMapping("/register")
    public String registerUser() {
        return "register";
    }

    @PostMapping("/register")
    public String registerUser(RequestUserDto RequestUserDto) {
        userService.add(RequestUserDto);
        return "redirect:/";
    }

    @RequestMapping("/login")
    public String login() {
        return "/index";
    }


}
