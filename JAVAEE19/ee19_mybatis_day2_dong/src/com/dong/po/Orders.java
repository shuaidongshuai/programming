package com.dong.po;

import java.sql.Date;

public class Orders {
	private int id;
	private int userId;
	private String number;
	private Date createtime;
	private String note;
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public int getUserId() {
		return userId;
	}
	public void setUserId(int userId) {
		this.userId = userId;
	}
	public String getNumber() {
		return number;
	}
	public void setNumber(String number) {
		this.number = number;
	}
	public Date getCreatetime() {
		return createtime;
	}
	public void setCreatetime(Date createtime) {
		this.createtime = createtime;
	}
	public String getNote() {
		return note;
	}
	public void setNote(String note) {
		this.note = note;
	}
	@Override
	public String toString() {
		return "Orders [id=" + id + ", userId=" + userId + ", number=" + number
				+ ", createtime=" + createtime + ", note=" + note + "]";
	}
}
