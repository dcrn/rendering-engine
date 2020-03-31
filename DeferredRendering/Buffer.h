#pragma once

#include <glbinding/gl/types.h>
#include <vector>

class Buffer
{
public:
	Buffer(gl::GLenum bufferType);
	~Buffer();


	template<typename ItemType, typename ValueType>
	void SetData(gl::GLenum valueType, std::vector<ItemType> data)
	{
		this->itemCount = static_cast<gl::GLsizei>(data.size());
		this->valueType = valueType;
		this->valueCount = static_cast<gl::GLsizei>(sizeof(ItemType) / sizeof(ValueType));
		LoadData(data.data(), data.size() * sizeof(ItemType));
	}

	bool IsValid() const;
	
	gl::GLuint GetId() const;
	gl::GLenum GetBufferType() const;
	gl::GLsizei GetItemCount() const;
	gl::GLsizei GetValueCount() const;
	gl::GLenum GetValueType() const;
	
private:
	void LoadData(const void* data, size_t size);
	
	gl::GLuint bufferId;
	gl::GLenum bufferType;
	gl::GLsizei itemCount;
	gl::GLsizei valueCount;
	gl::GLenum valueType;
};
