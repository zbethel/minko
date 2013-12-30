/*
Copyright (c) 2013 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "minko/Common.hpp"

#include "minko/data/Container.hpp"
#include "minko/data/Provider.hpp"

#include "minko/LuaWrapper.hpp"

namespace minko
{
	namespace data
	{
		class LuaContainer
		{
		public:
			static
			void
			bind(LuaGlue& state)
			{
				state.Class<Container>("Container")
		            //.method("create",       &Container::create)
		            //.method("hasProperty",  &Container::hasProperty)
					.method("addProvider",		static_cast<void (Container::*)(Provider::Ptr)>(&Container::addProvider))
					.method("removeProvider",	static_cast<void (Container::*)(Provider::Ptr)>(&Container::removeProvider))
					.method("hasProvider",		static_cast<bool (Container::*)(Provider::Ptr)>(&Container::hasProvider))
		            .method("getFloat",     	&Container::get<float>)
		            .method("getVector2",     	&Container::get<std::shared_ptr<math::Vector2>>)
		            .method("getVector3",     	&Container::get<std::shared_ptr<math::Vector3>>)
		            .method("getVector4",     	&Container::get<std::shared_ptr<math::Vector4>>)
		            .method("getInt",       	&Container::get<int>)
		            .method("getUint",      	&Container::get<unsigned int>)
		            .method("getMatrix4x4", 	&Container::get<std::shared_ptr<math::Matrix4x4>>);
			}
		};
	}
}
