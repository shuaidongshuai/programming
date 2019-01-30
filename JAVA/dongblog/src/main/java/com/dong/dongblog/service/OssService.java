package com.dong.dongblog.service;

import com.dong.dongblog.dto.ResponseUploadDto;
import com.dong.dongblog.model.User;

import java.io.UnsupportedEncodingException;

public interface OssService {
    ResponseUploadDto uploadAvatar(User user) throws UnsupportedEncodingException;

    ResponseUploadDto uploadBlogImage(User user) throws UnsupportedEncodingException;
}
