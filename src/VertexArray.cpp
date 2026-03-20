#include "VertexArray.h"
#include "App.h"
#include <iostream>

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_rendereID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_rendereID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)(uintptr_t)(offset)));
        offset += element.count * VertexBufferElement::GetSizeOffType(element.type);
    }
}

void VertexArray::Bind()
{
    GLCall(glBindVertexArray(m_rendereID));
}

void VertexArray::Unbind()
{
    GLCall(glBindVertexArray(0));
}
