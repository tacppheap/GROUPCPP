#pragma once

class proxy_store_element
{
public:
	proxy_store_element(void* _resource, void* _proxy) :resource_(_resource), proxy_(_proxy) {}
	void* resource_;
	void* proxy_;
};