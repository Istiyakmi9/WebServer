#pragma once

#include<iostream>

static class Constants
{
public:
	static int Ok();
	static int PageNotFount();
	static int InternalServerError();
	static int NoContent();
	static int UnAuthorized();
	static int BadRequest();

	enum class DataType {
		Int,
		Float,
		Double,
		String,
		Boolean,
		Char,
		DateTime
	};
};

