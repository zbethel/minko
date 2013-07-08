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
#include "minko/controller/AbstractController.hpp"

namespace minko
{
	namespace controller
	{
		class RenderingController :
			public AbstractController,
			public std::enable_shared_from_this<RenderingController>
		{
		public:
			typedef std::shared_ptr<RenderingController>		Ptr;

		private:
			typedef std::shared_ptr<scene::Node>				NodePtr;
			typedef std::shared_ptr<AbstractController>			AbsCtrlPtr;
			typedef std::shared_ptr<Surface>			SurfaceCtrlPtr;
			typedef std::shared_ptr<render::DrawCall>			DrawCallPtr;
			typedef std::shared_ptr<render::AbstractContext>	AbsContextPtr;
			typedef std::shared_ptr<scene::NodeSet>				NodeSetPtr;

		private:
			AbsContextPtr								_context;
			std::list<DrawCallPtr>						_drawCalls;
			NodeSetPtr									_surfaces;
			unsigned int								_backgroundColor;

			Signal<Ptr>::Ptr							_enterFrame;
			Signal<Ptr>::Ptr							_exitFrame;

			Signal<AbsCtrlPtr, NodePtr>::Slot			_targetAddedSlot;
			Signal<AbsCtrlPtr, NodePtr>::Slot			_targetRemovedSlot;
			Signal<NodeSetPtr, NodePtr>::Slot			_surfaceAddedSlot;
			Signal<NodeSetPtr, NodePtr>::Slot			_surfaceRemovedSlot;

		public:
			static
			Ptr
			create(AbsContextPtr context)
			{
				auto ctrl = std::shared_ptr<RenderingController>(new RenderingController(context));

				ctrl->initialize();

				return ctrl;
			}

			inline
			unsigned int
			backgroundColor()
			{
				return _backgroundColor;
			}

			inline
			void
			backgroundColor(const unsigned int backgroundColor)
			{
				_backgroundColor = backgroundColor;
			}

			void
			render();

			inline
			Signal<Ptr>::Ptr
			enterFrame()
			{
				return _enterFrame;
			}

			inline
			Signal<Ptr>::Ptr
			exitFrame()
			{
				return _exitFrame;
			}

		private:
			RenderingController(AbsContextPtr context);

			void
			initialize();

			void
			targetAddedHandler(AbsCtrlPtr ctrl, NodePtr target);

			void
			targetRemovedHandler(AbsCtrlPtr ctrl, NodePtr target);

			void
			surfaceAddedHandler(NodeSetPtr surfaces, NodePtr surfaceNode);

			void
			surfaceRemovedHandler(NodeSetPtr surfaces, NodePtr surfaceNode);

			void
			geometryChanged(SurfaceCtrlPtr ctrl);

			void
			materialChanged(SurfaceCtrlPtr ctrl);
		};
	}
}
