package com.dong.dongblog.test;

import com.dong.dongblog.dto.ElasticsearchBlogDto;
import org.springframework.data.elasticsearch.repository.ElasticsearchRepository;
import org.springframework.stereotype.Component;

@Component
public interface ElasticsearchBlogDao extends ElasticsearchRepository<ElasticsearchBlogDto, Long> {
}
