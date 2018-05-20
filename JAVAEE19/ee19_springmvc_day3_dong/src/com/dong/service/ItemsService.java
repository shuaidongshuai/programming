package com.dong.service;

import java.util.List;

import com.dong.domain.Items;

public interface ItemsService {

	List<Items> findAll();

	Items findItemById(int id);

	void update(Items item);

	void deleteById(int id);

	void deleteByIds(int[] ids);

}
