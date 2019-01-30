package com.dong.dongblog.service;

import com.dong.dongblog.dto.ElasticsearchBlogDto;

import java.util.List;

public interface ElasticsearchService {
    void addBlog(ElasticsearchBlogDto elasticsearchBlogDto);
    void delBlog(Long id);
    void updateBlog(ElasticsearchBlogDto elasticsearchBlogDto);
    ElasticsearchBlogDto getBlog(Long id);
    List<ElasticsearchBlogDto> getBlog(Integer pageNum, Integer pageSize, String query);
}
