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

#include "minko/math/AbstractShape.hpp"
#include "minko/math/Vector3.hpp"

namespace minko
{
	namespace math
	{
		class Box :
			public AbstractShape,
			public std::enable_shared_from_this<Box>
		{
		public:
			typedef std::shared_ptr<Box>	Ptr;

		private:
			std::shared_ptr<Vector3>	_topRight;
			std::shared_ptr<Vector3>	_bottomLeft;

		public:
			inline static
			Ptr
			create()
			{
				return std::shared_ptr<Box>(new Box());
			}

			inline static
			Ptr
			create(std::shared_ptr<math::Vector3> topRight, std::shared_ptr<math::Vector3> bottomLeft)
			{
				auto box = std::shared_ptr<Box>(new Box());

				box->_topRight->copyFrom(topRight);
				box->_bottomLeft->copyFrom(bottomLeft);

				return box;
			}

			static
			Ptr
			merge(Ptr box1, Ptr box2, Ptr out = nullptr);

			Ptr
			merge(Ptr box2);
			
			inline
			std::shared_ptr<Vector3>
			topRight() const
			{
				return _topRight;
			}

			inline
			std::shared_ptr<Vector3>
			bottomLeft() const
			{
				return _bottomLeft;
			}

			inline
			float
			width() const
			{
				return _topRight->x() - _bottomLeft->x();
			}

			inline
			float
			height() const
			{
				return _topRight->y() - _bottomLeft->y();
			}

			inline
			float
			depth() const
			{
				return _topRight->z() - _bottomLeft->z();
			}

			inline
			Ptr
			copyFrom(Ptr box)
			{
				_topRight->copyFrom(box->_topRight);
				_bottomLeft->copyFrom(box->_bottomLeft);

				return shared_from_this();
			}

			bool
			cast(std::shared_ptr<Ray> ray, float& distance);

			std::array<std::shared_ptr<Vector3>, 8>
			getVertices();

			
			ShapePosition
			testBoundingBox(std::shared_ptr<math::Box> box);

			void
			updateFromMatrix(std::shared_ptr<math::Matrix4x4> matrix);

		private:
			Box();
		};
	}
}