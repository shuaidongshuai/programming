package com.dong.dongblog.dto;

public class ResponseBlogSaveDto extends ResponseCommonDto {
    Long blogId;

    public Long getBlogId() {
        return blogId;
    }

    public void setBlogId(Long blogId) {
        this.blogId = blogId;
    }
}
