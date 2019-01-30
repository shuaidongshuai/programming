package com.dong.dongblog.service.impl;

import com.dong.dongblog.dto.ElasticsearchBlogDto;
import com.dong.dongblog.service.ElasticsearchService;
import com.dong.dongblog.test.ElasticsearchBlogDao;
import org.elasticsearch.index.query.MultiMatchQueryBuilder;
import org.elasticsearch.index.query.QueryBuilders;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class ElasticsearchServiceImpl implements ElasticsearchService {
    @Autowired
    ElasticsearchBlogDao elasticsearchBlogDao;

    @Override
    public void addBlog(ElasticsearchBlogDto elasticsearchBlogDto) {
        elasticsearchBlogDao.save(elasticsearchBlogDto);
    }

    @Override
    public void delBlog(Long id) {
        elasticsearchBlogDao.deleteById(id);
    }

    @Override
    public void updateBlog(ElasticsearchBlogDto elasticsearchBlogDto) {
        elasticsearchBlogDao.save(elasticsearchBlogDto);
    }

    @Override
    public ElasticsearchBlogDto getBlog(Long id) {
        Optional<ElasticsearchBlogDto> optional = elasticsearchBlogDao.findById(id);
        return optional.get();
    }

    @Override
    public List<ElasticsearchBlogDto> getBlog(Integer pageNum, Integer pageSize, String query) {
        MultiMatchQueryBuilder multiMatchQueryBuilder = QueryBuilders.multiMatchQuery(query, "title", "content");
        Page<ElasticsearchBlogDto> search = elasticsearchBlogDao.search(multiMatchQueryBuilder, new PageRequest(pageNum, pageSize));
        return search.getContent();
    }
}
