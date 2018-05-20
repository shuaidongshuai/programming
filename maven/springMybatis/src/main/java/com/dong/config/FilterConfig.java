package com.dong.config;

import javax.servlet.*;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

/**
 * 过滤器配置---这里并没有用到
 */
@WebFilter(filterName = "FilterConfig", urlPatterns = "/*") //拦截所有
public class FilterConfig implements Filter {

    @Override
    public void init(javax.servlet.FilterConfig filterConfig) throws ServletException {
        System.out.println("拦截请求");
    }

    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
        HttpServletRequest httpServletRequest = (HttpServletRequest) request;
        HttpServletResponse httpServletResponse = (HttpServletResponse) response;
        chain.doFilter(httpServletRequest, httpServletResponse);//放行
    }

    @Override
    public void destroy() {
        System.out.println("filter destroy method");
    }
}