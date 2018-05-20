package com.dong.dao;

import com.dong.domain.User;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;
import org.springframework.stereotype.Repository;

@Repository
public interface UserMapper {
    @Insert("insert into t_user(username, password) values(#{username}, #{password})")
    void insert(User record);

    @Delete("delete from t_user where id = #{id}")
    void delete(Integer id);

    @Select("select * from t_user where id = #{id}")
    User selectByPrimaryKey(Integer id);

    @Update("update t_user set username = #{username}, password = #{password} where id = #{id}")
    void updateByPrimaryKey(User record);
}