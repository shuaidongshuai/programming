package com.dong.controller;

import java.util.List;

import javax.annotation.Resource;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;

import com.dong.domain.Items;
import com.dong.service.ItemsService;

@Controller
@RequestMapping("items")
public class ItemsController {
	@Resource
	private ItemsService itemsService;
	
	//查询所有商品
	@RequestMapping("list")
	public String list(Model model){
		List<Items> itemsList = itemsService.findAll();
		//页面回显
		model.addAttribute("itemsList", itemsList);
		return "itemsList";
	}
	//跳转到修改页面
	@RequestMapping("edit")
	public String edit(int id, Model model){
		//根据Id查询商品
		Items item = itemsService.findItemById(id);
		model.addAttribute("item", item);
		return "editItem";
	}
	//提交修改页面
	@RequestMapping("editSubmit")
	public String editSubmit(Items item){
		itemsService.update(item);
		return "redirect:list.do";
	}
	//根据Id进行删除
	@RequestMapping("deleteById")
	public String deleteById(int id){
		itemsService.deleteById(id);
		return "redirect:list.do";
	}
	//批量删除
	@RequestMapping("deleteByIds")
	public String deleteByIds(int[] ids){
		itemsService.deleteByIds(ids);
		return "redirect:list.do";
	}
}
