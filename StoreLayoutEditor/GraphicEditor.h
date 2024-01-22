#pragma once

#include <typeinfo>

using namespace System;
using namespace System::Xml;

namespace Support {
	enum class Orientation { Horizontal, Vertical };
	enum class DragMode { None, Move, Resize };
	enum class Direction { Up, Down, Left, Right };
};

namespace Primitive {

	static public interface class UserControlSerializible {
		virtual void serialize(Xml::XmlWriter^);
		static Windows::Forms::UserControl^ deserialize(System::Xml::XmlReader^ reader) { throw gcnew NotImplementedException(); };
	};

	ref class GraphicElementContainer;

	public ref class GraphicElement abstract : Windows::Forms::UserControl {

	protected:
		bool isDragging;
		Drawing::Point previousLocation;
		GraphicElementContainer^ parentContainer;

	public:
		virtual void updateGraphic() = 0;

		virtual void SetParentContainer(GraphicElementContainer^ container) {
			parentContainer = container;
		}

		GraphicElementContainer^ GetParentContainer() {
			return parentContainer;
		}

	};

	public ref class GraphicElementContainer {

	private:
		Collections::Generic::List<GraphicElement^>^ GraphicElements;

	public:
		GraphicElementContainer(void) {
			this->GraphicElements = gcnew Collections::Generic::List<GraphicElement^>;
		}

		~GraphicElementContainer() {
			emptyGraphicElements();
		}

		void updateGraphic() {
			Collections::Generic::List<GraphicElement^>::Enumerator iteration = GraphicElements->GetEnumerator();
			while (iteration.MoveNext()) {
				(dynamic_cast<GraphicElement^>(iteration.Current))->updateGraphic();
			}
		}

		void addElement(GraphicElement^ e) {
			e->SetParentContainer(this);
			this->GraphicElements->Add(e);
		}

		void removeElement(GraphicElement^ e) {
			if (this->GraphicElements->Contains(e)) {
				this->GraphicElements->Remove(e);
			}
		}

		void emptyGraphicElements() {
			Collections::Generic::List<GraphicElement^>::Enumerator iteration = GraphicElements->GetEnumerator();
			while (iteration.MoveNext()) {
				delete dynamic_cast<GraphicElement^>(iteration.Current);
			}
			GraphicElements->Clear();
		}

		void serialize(Xml::XmlWriter^ writer) {
			writer->WriteStartElement("GraphicElementContainer");

			Collections::Generic::List<GraphicElement^>::Enumerator iteration = GraphicElements->GetEnumerator();
			while (iteration.MoveNext()) {
				auto serializableElement = dynamic_cast<UserControlSerializible^>(iteration.Current);
				if (serializableElement != nullptr) {
					serializableElement->serialize(writer);
				}
			}

			writer->WriteEndElement();
		}

		void deserialize(Xml::XmlReader^ reader, Windows::Forms::Control::ControlCollection^ parentControlContainer);
	};
}

namespace GraphicObject {
	public ref class DraggableRectangle : public Primitive::GraphicElement, Primitive::UserControlSerializible {
	public:
		DraggableRectangle(Drawing::Color color, int width, int height) {
			InitializeComponents();
			this->DoubleBuffered = true;
			this->BackColor = color;
			if (width > 10 && height > 10)
				this->Size = Drawing::Size(width, height);
			else if (height <= ResizeHandleSize) {
				this->Height = 10;
				this->Width = width;
			}
			else {
				this->Width = 10;
				this->Height = height;
			}
		}

		DraggableRectangle() {
			InitializeComponents();
			this->BackColor = Drawing::Color::Empty;
			this->Width = 10;
			this->Height = 10;
		}

		virtual void updateGraphic() override {
			this->Invalidate();
		}

		virtual void serialize(System::Xml::XmlWriter^ writer) override {
			writer->WriteStartElement(this->GetType()->Name);

			writer->WriteStartElement("Location");
			writer->WriteElementString("X", this->Location.X.ToString());
			writer->WriteElementString("Y", this->Location.Y.ToString());
			writer->WriteEndElement();

			writer->WriteStartElement("Size");
			writer->WriteElementString("Width", this->Size.Width.ToString());
			writer->WriteElementString("Height", this->Size.Height.ToString());
			writer->WriteEndElement();

			writer->WriteStartElement("BackColor");
			writer->WriteElementString("ARGB", this->BackColor.ToArgb().ToString());
			writer->WriteEndElement();

			writer->WriteEndElement();
		}

		static DraggableRectangle^ deserialize(System::Xml::XmlReader^ reader) {
			DraggableRectangle^ rectangle = gcnew DraggableRectangle();
			reader->Read();
			if (reader->Name == "Location") {
				reader->ReadStartElement();
				int x = Int32::Parse(reader->ReadElementString("X"));
				int y = Int32::Parse(reader->ReadElementString("Y"));
				rectangle->Location = Drawing::Point(x, y);
				reader->ReadEndElement();
			}
			if (reader->Name == "Size") {
				reader->ReadStartElement();
				int width = Int32::Parse(reader->ReadElementString("Width"));
				int height = Int32::Parse(reader->ReadElementString("Height"));
				rectangle->Size = Drawing::Size(width, height);
				reader->ReadEndElement();
			}
			if (reader->Name == "BackColor") {
				reader->ReadStartElement();
				String^ argbValue = reader->ReadElementString("ARGB");
				rectangle->BackColor = Drawing::Color::FromArgb(Int32::Parse(argbValue));
				reader->ReadEndElement();
			}

			return rectangle;
		}

	protected:
		literal int ResizeHandleSize = 8;
		Support::DragMode dragMode = Support::DragMode::None;
		Drawing::Point resizeStartPoint;
		bool showResizeHandle;

		virtual bool IsInResizeZone(Drawing::Point point) {
			return point.X >= this->Width - ResizeHandleSize && point.Y >= this->Height - ResizeHandleSize;
		}

		System::ComponentModel::Container^ components;
		virtual void InitializeComponents() {
			components = gcnew System::ComponentModel::Container();
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &DraggableRectangle::OnMouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &DraggableRectangle::OnMouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &DraggableRectangle::OnMouseUp);
			this->MouseEnter += gcnew EventHandler(this, &DraggableRectangle::OnMouseEnter);
			this->MouseLeave += gcnew EventHandler(this, &DraggableRectangle::OnMouseLeave);
		}

		virtual void OnMouseDown(Object^ sender, Windows::Forms::MouseEventArgs^ e) override {
			if (e->Button == System::Windows::Forms::MouseButtons::Left) {
				this->previousLocation = e->Location;

				if (IsInResizeZone(e->Location)) {
					dragMode = Support::DragMode::Resize;
					resizeStartPoint = this->PointToScreen(e->Location);
				}
				else {
					dragMode = Support::DragMode::Move;
				}
				isDragging = true;
				this->Capture = true;
			}
			if (e->Button == System::Windows::Forms::MouseButtons::Right) {
				auto container = this->GetParentContainer();
				if (container != nullptr) {
					container->removeElement(this);
					if (this->Parent != nullptr) {
						this->Parent->Controls->Remove(this);
					}
					delete this;
				}
			}
		}

		virtual void OnMouseMove(Object^ sender, Windows::Forms::MouseEventArgs^ e) override {
			if (!isDragging) return;

			if (dragMode == Support::DragMode::Move) {
				this->Location = Drawing::Point(this->Left + e->X - previousLocation.X, this->Top + e->Y - previousLocation.Y);
			}
			else if (dragMode == Support::DragMode::Resize) {
				Drawing::Point screenPoint = this->PointToScreen(e->Location);
				this->Width = Math::Max(this->Width + screenPoint.X - resizeStartPoint.X, ResizeHandleSize * 2);
				this->Height = Math::Max(this->Height + screenPoint.Y - resizeStartPoint.Y, ResizeHandleSize * 2);
				resizeStartPoint = screenPoint;
			}

			this->Invalidate();
		}

		virtual void OnMouseUp(Object^ sender, Windows::Forms::MouseEventArgs^ e) override {
			if (e->Button == System::Windows::Forms::MouseButtons::Left) {
				this->Capture = false;
				isDragging = false;
				dragMode = Support::DragMode::None;
			}
		}

		virtual void OnMouseEnter(Object^ sender, EventArgs^ e) {
			showResizeHandle = true;
			this->Invalidate();
		}

		virtual void OnMouseLeave(Object^ sender, EventArgs^ e) {
			showResizeHandle = false;
			this->Invalidate();
		}

		virtual void OnPaint(Windows::Forms::PaintEventArgs^ e) override {
			GraphicElement::OnPaint(e);

			if (showResizeHandle) {
				e->Graphics->FillRectangle(gcnew Drawing::SolidBrush(Drawing::Color::Black),
					this->Width - ResizeHandleSize,
					this->Height - ResizeHandleSize,
					ResizeHandleSize,
					ResizeHandleSize);
			}
		}
	};


	public ref class FixedSideRectangle : public DraggableRectangle, Primitive::UserControlSerializible {
	public:
		FixedSideRectangle(Drawing::Color color, Support::Orientation orientation, int width, int height)
			: DraggableRectangle(color, width, height), orientation(orientation) {}

		FixedSideRectangle() : DraggableRectangle(), orientation(Support::Orientation::Horizontal) {}

		virtual void serialize(System::Xml::XmlWriter^ writer) override {
			writer->WriteStartElement(this->GetType()->Name);

			writer->WriteStartElement("Location");
			writer->WriteElementString("X", this->Location.X.ToString());
			writer->WriteElementString("Y", this->Location.Y.ToString());
			writer->WriteEndElement();

			writer->WriteStartElement("Size");
			writer->WriteElementString("Width", this->Size.Width.ToString());
			writer->WriteElementString("Height", this->Size.Height.ToString());
			writer->WriteEndElement();

			writer->WriteStartElement("BackColor");
			writer->WriteElementString("ARGB", this->BackColor.ToArgb().ToString());
			writer->WriteEndElement();

			writer->WriteStartElement("Orientation");
			writer->WriteElementString("FixedSide", ((int)orientation).ToString());
			writer->WriteEndElement();

			writer->WriteEndElement();
		}

		static FixedSideRectangle^ deserialize(System::Xml::XmlReader^ reader) {
			FixedSideRectangle^ rectangle = gcnew FixedSideRectangle();
			reader->Read();
			if (reader->Name == "Location") {
				reader->ReadStartElement();
				int x = Int32::Parse(reader->ReadElementString("X"));
				int y = Int32::Parse(reader->ReadElementString("Y"));
				rectangle->Location = Drawing::Point(x, y);
				reader->ReadEndElement();
			}
			if (reader->Name == "Size") {
				reader->ReadStartElement();
				int width = Int32::Parse(reader->ReadElementString("Width"));
				int height = Int32::Parse(reader->ReadElementString("Height"));
				rectangle->Size = Drawing::Size(width, height);
				reader->ReadEndElement();
			}
			if (reader->Name == "BackColor") {
				reader->ReadStartElement();
				String^ argbValue = reader->ReadElementString("ARGB");
				rectangle->BackColor = Drawing::Color::FromArgb(Int32::Parse(argbValue));
				reader->ReadEndElement();
			}
			if (reader->Name == "Orientation") {
				reader->ReadStartElement();
				int orientationValue = Int32::Parse(reader->ReadElementString("Orientation"));
				rectangle->orientation = (Support::Orientation)orientationValue;
				reader->ReadEndElement();
			}

			return rectangle;
		}

	protected:
		Support::Orientation orientation;

		virtual void OnMouseMove(Object^ sender, Windows::Forms::MouseEventArgs^ e) override {
			if (!isDragging) return;

			if (dragMode == Support::DragMode::Move) {
				this->Location = Drawing::Point(this->Left + e->X - previousLocation.X, this->Top + e->Y - previousLocation.Y);
			}
			else if (dragMode == Support::DragMode::Resize) {
				Drawing::Point screenPoint = this->PointToScreen(e->Location);

				switch (orientation) {
				case Support::Orientation::Vertical:
					this->Height = Math::Max(this->Height + screenPoint.Y - resizeStartPoint.Y, ResizeHandleSize * 2);
					resizeStartPoint.Y = screenPoint.Y;
					break;
				case Support::Orientation::Horizontal:
					this->Width = Math::Max(this->Width + screenPoint.X - resizeStartPoint.X, ResizeHandleSize * 2);
					resizeStartPoint.X = screenPoint.X;
					break;
				}
			}

			this->Invalidate();
		}
	};

	public ref class Arrow : public FixedSideRectangle, Primitive::UserControlSerializible {
	public:

		Arrow(Support::Direction direction) {
			InitializeComponents();
			this->DoubleBuffered = true;
			this->direction = direction;
			this->orientation = GetOrientation(this->direction);
			this->BackColor = Drawing::Color::Empty;
			this->Width = 16;
			this->Height = 16;
			setTrianglePoints();
			setShaftPoints();
			this->MouseMove -= gcnew System::Windows::Forms::MouseEventHandler(this, &Arrow::OnMouseMove);
		}

		Arrow() : FixedSideRectangle() {
			InitializeComponents();
			this->DoubleBuffered = true;
			this->direction = Support::Direction::Up;
			this->orientation = GetOrientation(this->direction);
			this->BackColor = Drawing::Color::Empty;
			this->Width = 16;
			this->Height = 16;
			setTrianglePoints();
			setShaftPoints();
			this->MouseMove -= gcnew System::Windows::Forms::MouseEventHandler(this, &Arrow::OnMouseMove);
		}

		virtual void serialize(System::Xml::XmlWriter^ writer) override {
			writer->WriteStartElement(this->GetType()->Name);

			writer->WriteStartElement("Location");
			writer->WriteElementString("X", this->Location.X.ToString());
			writer->WriteElementString("Y", this->Location.Y.ToString());
			writer->WriteEndElement();

			writer->WriteStartElement("Size");
			writer->WriteElementString("Width", this->Size.Width.ToString());
			writer->WriteElementString("Height", this->Size.Height.ToString());
			writer->WriteEndElement();

			writer->WriteStartElement("BackColor");
			writer->WriteElementString("ARGB", this->BackColor.ToArgb().ToString());
			writer->WriteEndElement();

			writer->WriteStartElement("Orientation");
			writer->WriteElementString("FixedSide", ((int)orientation).ToString());
			writer->WriteEndElement();

			writer->WriteStartElement("Direction");
			writer->WriteElementString("Value", ((int)direction).ToString());
			writer->WriteEndElement();

			writer->WriteEndElement();
		}

		static Arrow^ deserialize(System::Xml::XmlReader^ reader) {
			Arrow^ arrow = gcnew Arrow();
			reader->Read();
			if (reader->Name == "Location") {
				reader->ReadStartElement();
				int x = Int32::Parse(reader->ReadElementString("X"));
				int y = Int32::Parse(reader->ReadElementString("Y"));
				arrow->Location = Drawing::Point(x, y);
				reader->ReadEndElement();
			}
			if (reader->Name == "Size") {
				reader->ReadStartElement();
				int width = Int32::Parse(reader->ReadElementString("Width"));
				int height = Int32::Parse(reader->ReadElementString("Height"));
				arrow->Size = Drawing::Size(width, height);
				reader->ReadEndElement();
			}
			if (reader->Name == "BackColor") {
				reader->ReadStartElement();
				String^ argbValue = reader->ReadElementString("ARGB");
				arrow->BackColor = Drawing::Color::FromArgb(Int32::Parse(argbValue));
				reader->ReadEndElement();
			}
			if (reader->Name == "Orientation") {
				reader->ReadStartElement();
				int orientationValue = Int32::Parse(reader->ReadElementString("FixedSide"));
				arrow->orientation = (Support::Orientation)orientationValue;
				reader->ReadEndElement();
			}
			if (reader->Name == "Direction") {
				reader->ReadStartElement();
				int directionValue = Int32::Parse(reader->ReadElementString("Value"));
				arrow->direction = (Support::Direction)directionValue;
				reader->ReadEndElement();
			}

			return arrow;
		}

	protected:
		Support::Direction direction;
		Drawing::Point ResizeHandleLocation;
		array<Drawing::Point>^ trianglePoints = gcnew array<Drawing::Point>(3);
		array<Drawing::Point>^ shaftPoints = gcnew array<Drawing::Point>(4);

		virtual bool IsInResizeZone(Drawing::Point point) override {
			return (point.X >= ResizeHandleLocation.X && point.X <= ResizeHandleLocation.X + ResizeHandleSize) &&
				(point.Y >= ResizeHandleLocation.Y && point.Y <= ResizeHandleLocation.Y + ResizeHandleSize);
		}

		static Support::Orientation GetOrientation(Support::Direction direction) {
			switch (direction) {
			case Support::Direction::Up:
			case Support::Direction::Down:
				return Support::Orientation::Vertical;
			case Support::Direction::Left:
			case Support::Direction::Right:
				return Support::Orientation::Horizontal;
			}
		}

		virtual void setTrianglePoints() {
			switch (direction) {
			case Support::Direction::Up:
				trianglePoints[0] = Drawing::Point(this->Width / 2, 0);
				trianglePoints[1] = Drawing::Point(this->Width / 2 - ResizeHandleSize, ResizeHandleSize);
				trianglePoints[2] = Drawing::Point(this->Width / 2 + ResizeHandleSize, ResizeHandleSize);
				break;
			case Support::Direction::Down:
				trianglePoints[0] = Drawing::Point(this->Width / 2, this->Height);
				trianglePoints[1] = Drawing::Point(this->Width / 2 - ResizeHandleSize, this->Height - ResizeHandleSize);
				trianglePoints[2] = Drawing::Point(this->Width / 2 + ResizeHandleSize, this->Height - ResizeHandleSize);
				break;
			case Support::Direction::Left:
				trianglePoints[0] = Drawing::Point(0, this->Height / 2);
				trianglePoints[1] = Drawing::Point(ResizeHandleSize, this->Height / 2 - ResizeHandleSize);
				trianglePoints[2] = Drawing::Point(ResizeHandleSize, this->Height / 2 + ResizeHandleSize);
				break;
			case Support::Direction::Right:
				trianglePoints[0] = Drawing::Point(this->Width, this->Height / 2);
				trianglePoints[1] = Drawing::Point(this->Width - ResizeHandleSize, this->Height / 2 - ResizeHandleSize);
				trianglePoints[2] = Drawing::Point(this->Width - ResizeHandleSize, this->Height / 2 + ResizeHandleSize);
				break;
			}
		}

		virtual void setShaftPoints() {
			switch (direction) {
			case Support::Direction::Up:
				shaftPoints[0] = Drawing::Point(ResizeHandleSize / 2, ResizeHandleSize);
				shaftPoints[1] = Drawing::Point(this->Width - ResizeHandleSize / 2, ResizeHandleSize);
				shaftPoints[2] = Drawing::Point(this->Width - ResizeHandleSize / 2, this->Height);
				shaftPoints[3] = Drawing::Point(ResizeHandleSize / 2, this->Height);
				break;
			case Support::Direction::Down:
				shaftPoints[0] = Drawing::Point(ResizeHandleSize / 2, 0);
				shaftPoints[1] = Drawing::Point(this->Width - ResizeHandleSize / 2, 0);
				shaftPoints[2] = Drawing::Point(this->Width - ResizeHandleSize / 2, this->Height - ResizeHandleSize);
				shaftPoints[3] = Drawing::Point(ResizeHandleSize / 2, this->Height - ResizeHandleSize);
				break;
			case Support::Direction::Left:
				shaftPoints[0] = Drawing::Point(ResizeHandleSize, ResizeHandleSize / 2);
				shaftPoints[1] = Drawing::Point(ResizeHandleSize, this->Height - ResizeHandleSize / 2);
				shaftPoints[2] = Drawing::Point(this->Width, this->Height - ResizeHandleSize / 2);
				shaftPoints[3] = Drawing::Point(this->Width, ResizeHandleSize / 2);
				break;
			case Support::Direction::Right:
				shaftPoints[0] = Drawing::Point(0, ResizeHandleSize / 2);
				shaftPoints[1] = Drawing::Point(0, this->Height - ResizeHandleSize / 2);
				shaftPoints[3] = Drawing::Point(this->Width - ResizeHandleSize, ResizeHandleSize / 2);
				shaftPoints[2] = Drawing::Point(this->Width - ResizeHandleSize, this->Height - ResizeHandleSize / 2);
				break;
			}
		}

		virtual void OnPaint(Windows::Forms::PaintEventArgs^ e) override {
			GraphicElement::OnPaint(e);

			setTrianglePoints();
			setShaftPoints();

			e->Graphics->FillPolygon(gcnew Drawing::SolidBrush(Drawing::Color::Black), trianglePoints);
			e->Graphics->FillPolygon(gcnew Drawing::SolidBrush(Drawing::Color::Black), shaftPoints);

			if (showResizeHandle) {
				ResizeHandleLocation = CalculateResizeHandleLocation();
				e->Graphics->FillRectangle(gcnew Drawing::SolidBrush(Drawing::Color::Gold),
					ResizeHandleLocation.X,
					ResizeHandleLocation.Y,
					ResizeHandleSize,
					ResizeHandleSize);
			}
		}

		Drawing::Point CalculateResizeHandleLocation() {
			int x = 0;
			int y = 0;

			switch (direction) {
			case Support::Direction::Down:
				x = (this->Width - ResizeHandleSize) / 2;
				y = 0;
				break;
			case Support::Direction::Up:
				x = (this->Width - ResizeHandleSize) / 2;
				y = this->Height - ResizeHandleSize;
				break;
			case Support::Direction::Right:
				x = 0;
				y = (this->Height - ResizeHandleSize) / 2;
				break;
			case Support::Direction::Left:
				x = this->Width - ResizeHandleSize;
				y = (this->Height - ResizeHandleSize) / 2;
				break;
			}

			return Drawing::Point(x, y);
		}
	};

	ref class WallFeature;

	public ref class Wall : public FixedSideRectangle, Primitive::UserControlSerializible {
	protected:
		Collections::Generic::List<WallFeature^>^ features;
		Primitive::GraphicElementContainer^ container;

		virtual void OnMouseClick(Windows::Forms::MouseEventArgs^ e) override {
			if (e->Button == System::Windows::Forms::MouseButtons::Right) {
				Windows::Forms::ContextMenu^ menu = gcnew Windows::Forms::ContextMenu();
				Windows::Forms::MenuItem^ addDoorItem = gcnew Windows::Forms::MenuItem("Добавить дверь", gcnew EventHandler(this, &Wall::OnAddFeature));
				Windows::Forms::MenuItem^ addWindowItem = gcnew Windows::Forms::MenuItem("Добавить окно", gcnew EventHandler(this, &Wall::OnAddFeature));
				Windows::Forms::MenuItem^ addOpeningItem = gcnew Windows::Forms::MenuItem("Добавить проем", gcnew EventHandler(this, &Wall::OnAddFeature));
				Windows::Forms::MenuItem^ deleteWallItem = gcnew Windows::Forms::MenuItem("Удалить стену", gcnew EventHandler(this, &Wall::OnDeleteWallSelected));

				menu->MenuItems->Add(addDoorItem);
				menu->MenuItems->Add(addWindowItem);
				menu->MenuItems->Add(addOpeningItem);
				menu->MenuItems->Add(deleteWallItem);

				menu->Show(this, e->Location);
			}
			FixedSideRectangle::OnMouseClick(e);
		}

		virtual void OnMouseDown(Object^ sender, Windows::Forms::MouseEventArgs^ e) override {
			if (e->Button == System::Windows::Forms::MouseButtons::Left) {
				this->previousLocation = e->Location;

				if (IsInResizeZone(e->Location)) {
					dragMode = Support::DragMode::Resize;
					resizeStartPoint = this->PointToScreen(e->Location);
					this->Capture = true;
				}
				else {
					dragMode = Support::DragMode::Move;
					this->Capture = true;
				}
				isDragging = true;
			}
		}

		void OnDeleteWallSelected(Object^ sender, EventArgs^ e) {
			auto container = this->GetParentContainer();
			if (container != nullptr) {
				container->removeElement(this);
				if (this->Parent != nullptr) {
					this->Parent->Controls->Remove(this);
				}
				delete this;
			}
		}

		void OnAddFeature(Object^ sender, EventArgs^ e);


	public:
		Wall(Drawing::Color color, Support::Orientation orientation, int width, int height)
			: FixedSideRectangle(color, orientation, width, height),
			container(gcnew Primitive::GraphicElementContainer()),
			features(gcnew Collections::Generic::List<WallFeature^>()) {}

		Wall() : FixedSideRectangle(),
			container(gcnew Primitive::GraphicElementContainer()),
			features(gcnew Collections::Generic::List<WallFeature^>()) {}

		~Wall() {
			if (features) {
				features->Clear();
				features = nullptr;
			}
		}

		void removeWallFeature(WallFeature^ e) {
			if (this->features->Contains(e)) {
				this->features->Remove(e);
			}
		}

		int GetWallWidth() {
			return this->Width;
		}

		int GetWallHeight() {
			return this->Height;
		}

		void AddWallFeature(WallFeature^ feature);

		virtual void serialize(System::Xml::XmlWriter^ writer) override;

		static Wall^ deserialize(System::Xml::XmlReader^ reader);

	};

	public ref class WallFeature : public FixedSideRectangle {
	public:
		WallFeature(Drawing::Color color, Support::Orientation orientation, int dimension, Wall^ wall)
			: FixedSideRectangle(color, orientation, dimension, dimension), parentWall(wall) {}

		WallFeature() : FixedSideRectangle() {};

		void SetParentWall(Wall^ wall) {
			parentWall = wall;
		}

		virtual void serialize(System::Xml::XmlWriter^ writer) override {
			writer->WriteStartElement(this->GetType()->Name);

			writer->WriteStartElement("Location");
			writer->WriteElementString("X", this->Location.X.ToString());
			writer->WriteElementString("Y", this->Location.Y.ToString());
			writer->WriteEndElement();

			writer->WriteStartElement("Size");
			writer->WriteElementString("Width", this->Size.Width.ToString());
			writer->WriteElementString("Height", this->Size.Height.ToString());
			writer->WriteEndElement();

			writer->WriteStartElement("BackColor");
			writer->WriteElementString("ARGB", this->BackColor.ToArgb().ToString());
			writer->WriteEndElement();

			writer->WriteStartElement("Orientation");
			writer->WriteElementString("FixedSide", ((int)orientation).ToString());
			writer->WriteEndElement();

			writer->WriteEndElement();
		}

		static WallFeature^ deserialize(System::Xml::XmlReader^ reader) {
			WallFeature^ wallFeature = gcnew WallFeature();
			reader->Read();
			if (reader->Name == "Location") {
				reader->ReadStartElement();
				int x = Int32::Parse(reader->ReadElementString("X"));
				int y = Int32::Parse(reader->ReadElementString("Y"));
				wallFeature->Location = Drawing::Point(x, y);
				reader->ReadEndElement();
			}
			if (reader->Name == "Size") {
				reader->ReadStartElement();
				int width = Int32::Parse(reader->ReadElementString("Width"));
				int height = Int32::Parse(reader->ReadElementString("Height"));
				wallFeature->Size = Drawing::Size(width, height);
				reader->ReadEndElement();
			}
			if (reader->Name == "BackColor") {
				reader->ReadStartElement();
				String^ argbValue = reader->ReadElementString("ARGB");
				wallFeature->BackColor = Drawing::Color::FromArgb(Int32::Parse(argbValue));
				reader->ReadEndElement();
			}
			if (reader->Name == "Orientation") {
				reader->ReadStartElement();
				int orientationValue = Int32::Parse(reader->ReadElementString("FixedSide"));
				wallFeature->orientation = (Support::Orientation)orientationValue;
				reader->ReadEndElement();
			}

			return wallFeature;
		}

	protected:
		Wall^ parentWall;

		virtual void OnMouseMove(Object^ sender, Windows::Forms::MouseEventArgs^ e) override {
			if (isDragging) {
				Wall^ wall = dynamic_cast<Wall^>(this->Parent);

				if (dragMode == Support::DragMode::Move) {
					int newX = this->Left + e->X - previousLocation.X;
					int newY = this->Top + e->Y - previousLocation.Y;

					newX = Math::Max(newX, 0);
					newY = Math::Max(newY, 0);
					newX = Math::Min(newX, wall->Width - this->Width);
					newY = Math::Min(newY, wall->Height - this->Height);

					this->Location = Drawing::Point(newX, newY);
				}
				else if (dragMode == Support::DragMode::Resize) {
					if (orientation == Support::Orientation::Horizontal) {
						int newWidth = e->X;
						newWidth = Math::Max(newWidth, ResizeHandleSize * 2);
						newWidth = Math::Min(newWidth, wall->Width - this->Left);
						this->Width = newWidth;
					}
					else {
						int newHeight = e->Y;
						newHeight = Math::Max(newHeight, ResizeHandleSize * 2);
						newHeight = Math::Min(newHeight, wall->Height - this->Top);
						this->Height = newHeight;
					}
				}
				this->Invalidate();
			}
		}

		virtual void OnMouseDown(Object^ sender, Windows::Forms::MouseEventArgs^ e) override {
			if (e->Button == System::Windows::Forms::MouseButtons::Left) {
				Wall^ wall = dynamic_cast<Wall^>(this->Parent);
				this->previousLocation = e->Location;

				if (IsInResizeZone(e->Location)) {
					dragMode = Support::DragMode::Resize;
					resizeStartPoint = Drawing::Point(
						Math::Min(e->Location.X, wall->Width - this->Left),
						Math::Min(e->Location.Y, wall->Height - this->Top)
					);
					isDragging = true;
					this->Capture = true;
				}
			}
			if (e->Button == System::Windows::Forms::MouseButtons::Right) {
				auto container = this->GetParentContainer();
				if (container != nullptr) {
					container->removeElement(this);
					if (this->Parent != nullptr) {
						this->Parent->Controls->Remove(this);
					}
					this->parentWall->removeWallFeature(this);
					delete this;
				}
			}
		}
	};

	inline void Wall::AddWallFeature(WallFeature^ feature) {
		container->addElement(feature);
		features->Add(feature);
		feature->SetParentContainer(this->container);
		this->Controls->Add(feature);
	}

	inline void Wall::OnAddFeature(Object^ sender, EventArgs^ e) {
		Windows::Forms::MenuItem^ menuItem = safe_cast<Windows::Forms::MenuItem^>(sender);
		String^ featureType = menuItem->Text;
		WallFeature^ newFeature = nullptr;

		if (featureType == "Добавить дверь") {
			if (this->orientation == Support::Orientation::Horizontal)
				newFeature = gcnew WallFeature(Drawing::Color::DarkRed, this->orientation, this->Height, this);
			else
				newFeature = gcnew WallFeature(Drawing::Color::DarkRed, this->orientation, this->Width, this);
		}
		else if (featureType == "Добавить окно") {
			if (this->orientation == Support::Orientation::Horizontal)
				newFeature = gcnew WallFeature(Drawing::Color::LightSkyBlue, this->orientation, this->Height, this);
			else
				newFeature = gcnew WallFeature(Drawing::Color::LightSkyBlue, this->orientation, this->Width, this);
		}
		else if (featureType == "Добавить проем") {
			if (this->orientation == Support::Orientation::Horizontal)
				newFeature = gcnew WallFeature(Drawing::Color::LightGray, this->orientation, this->Height, this);
			else
				newFeature = gcnew WallFeature(Drawing::Color::LightGray, this->orientation, this->Width, this);
		}

		if (newFeature != nullptr) {
			AddWallFeature(newFeature);
		}
	}

	inline void Wall::serialize(System::Xml::XmlWriter^ writer) {
		writer->WriteStartElement(this->GetType()->Name);

		writer->WriteStartElement("Location");
		writer->WriteElementString("X", this->Location.X.ToString());
		writer->WriteElementString("Y", this->Location.Y.ToString());
		writer->WriteEndElement();

		writer->WriteStartElement("Size");
		writer->WriteElementString("Width", this->Size.Width.ToString());
		writer->WriteElementString("Height", this->Size.Height.ToString());
		writer->WriteEndElement();

		writer->WriteStartElement("BackColor");
		writer->WriteElementString("ARGB", this->BackColor.ToArgb().ToString());
		writer->WriteEndElement();

		writer->WriteStartElement("Orientation");
		writer->WriteElementString("FixedSide", ((int)orientation).ToString());
		writer->WriteEndElement();

		writer->WriteStartElement("Features");
		if (this->features->Count > 0) {
			for each (WallFeature ^ feature in features) {
				feature->serialize(writer);
			}
		}
		else
			writer->WriteString("None");
		writer->WriteEndElement();

		writer->WriteEndElement();
	}

	inline Wall^ Wall::deserialize(System::Xml::XmlReader^ reader) {
		Wall^ wall = gcnew Wall();
		reader->Read();
		if (reader->Name == "Location") {
			reader->ReadStartElement();
			int x = Int32::Parse(reader->ReadElementString("X"));
			int y = Int32::Parse(reader->ReadElementString("Y"));
			wall->Location = Drawing::Point(x, y);
			reader->ReadEndElement();
		}
		if (reader->Name == "Size") {
			reader->ReadStartElement();
			int width = Int32::Parse(reader->ReadElementString("Width"));
			int height = Int32::Parse(reader->ReadElementString("Height"));
			wall->Size = Drawing::Size(width, height);
			reader->ReadEndElement();
		}
		if (reader->Name == "BackColor") {
			reader->ReadStartElement();
			String^ argbValue = reader->ReadElementString("ARGB");
			wall->BackColor = Drawing::Color::FromArgb(Int32::Parse(argbValue));
			reader->ReadEndElement();
		}
		if (reader->Name == "Orientation") {
			reader->ReadStartElement();
			int orientationValue = Int32::Parse(reader->ReadElementString("FixedSide"));
			wall->orientation = (Support::Orientation)orientationValue;
			reader->ReadEndElement();
		}
		if (reader->Name == "Features") {

			while (!(reader->NodeType == XmlNodeType::EndElement && reader->Name == "Features") && reader->Read()) {
				if (reader->NodeType == XmlNodeType::Element) {
					WallFeature^ feature = WallFeature::deserialize(reader);
					feature->SetParentWall(wall);
					wall->AddWallFeature(feature);
				}
			}
			reader->ReadEndElement();
		}

		return wall;
	}
}

namespace Primitive {
	inline void GraphicElementContainer::deserialize(Xml::XmlReader^ reader, Windows::Forms::Control::ControlCollection^ parentControlContainer) {
		if (reader->MoveToContent() == XmlNodeType::Element && reader->Name == "GraphicElementContainer") {
			while (reader->Read()) {
				if (reader->NodeType == XmlNodeType::EndElement && reader->Name == "GraphicElementContainer") {
					break;
				}

				if (reader->NodeType == XmlNodeType::Element) {
					String^ typeName = reader->Name;
					GraphicElement^ element = nullptr;

					try {
						if (typeName == "DraggableRectangle") {
							element = GraphicObject::DraggableRectangle::deserialize(reader);
						}
						else if (typeName == "FixedSideRectangle") {
							element = GraphicObject::FixedSideRectangle::deserialize(reader);
						}
						else if (typeName == "Wall") {
							element = GraphicObject::Wall::deserialize(reader);
						}
						else if (typeName == "Arrow") {
							element = GraphicObject::Arrow::deserialize(reader);
						}
						if (element != nullptr) {
							this->addElement(element);

							if (parentControlContainer != nullptr) {
								parentControlContainer->Add(element);
							}
						}
					}
					catch (NotImplementedException^) {
						throw gcnew NotImplementedException();
					}
				}
			}
		}

		Collections::Generic::List<GraphicElement^>::Enumerator iteration = this->GraphicElements->GetEnumerator();

		while (iteration.MoveNext()) {
			GraphicObject::Arrow^ specificElement = dynamic_cast<GraphicObject::Arrow^>(iteration.Current);
			if (specificElement != nullptr) {
				parentControlContainer->SetChildIndex(specificElement, parentControlContainer->Count - 1);
				specificElement->BringToFront();
			}
		}
	}
}