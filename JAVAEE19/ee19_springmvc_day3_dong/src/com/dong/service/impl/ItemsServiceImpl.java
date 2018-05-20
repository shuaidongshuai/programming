package com.dong.service.impl;

import java.util.List;

import javax.annotation.Resource;

import org.springframework.stereotype.Service;

import com.dong.dao.ItemsMapper;
import com.dong.domain.Items;
import com.dong.service.ItemsService;

@Service
public class ItemsServiceImpl implements ItemsService {
	@Resource
	private ItemsMapper itemsMapper;
	@Override
	public List<Items> findAll() {
		List<Items> items = itemsMapper.findAll();
		return items;
	}
	@Override
	public Items findItemById(int id) {
		Items item = itemsMapper.selectByPrimaryKey(id);
		return item;
	}
	@Override
	public void update(Items item) {
		itemsMapper.updateByPrimaryKey(item);
	}
	@Override
	public void deleteById(int id) {
		itemsMapper.deleteByPrimaryKey(id);
	}
	@Override
	public void deleteByIds(int[] ids) {
		if(ids != null){
			for(int id : ids){
				itemsMapper.deleteByPrimaryKey(id);
			}
		}
	}
	
}
