#pragma once

using namespace System;
using namespace System::Xml;

namespace Support {
	enum class Orientation { Horizontal, Vertical };
	enum class DragMode { None, Move, Resize };
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

		virtual void onMouseUp(Object^ sender, Windows::Forms::MouseEventArgs^ e) {};
		virtual void onMouseDown(Object^ sender, Windows::Forms::MouseEventArgs^ e) {};
		virtual void onMouseMove(Object^ sender, Windows::Forms::MouseEventArgs^ e) {};

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
		int dragOffsetX;
		int dragOffsetY;
		Drawing::Point resizeStartPoint;
		bool showResizeHandle;

		bool IsInResizeZone(Drawing::Point point) {
			return point.X >= this->Width - ResizeHandleSize && point.Y >= this->Height - ResizeHandleSize;
		}


		System::ComponentModel::Container^ components;
		void InitializeComponents() {
			components = gcnew System::ComponentModel::Container();
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &DraggableRectangle::onMouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &DraggableRectangle::onMouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &DraggableRectangle::onMouseUp);
			this->MouseEnter += gcnew EventHandler(this, &DraggableRectangle::OnMouseEnter);
			this->MouseLeave += gcnew EventHandler(this, &DraggableRectangle::OnMouseLeave);
		}

		virtual void onMouseDown(Object^ sender, Windows::Forms::MouseEventArgs^ e) override {
			if (e->Button == System::Windows::Forms::MouseButtons::Left) {
				dragOffsetX = e->X;
				dragOffsetY = e->Y;

				if (IsInResizeZone(e->Location)) {
					dragMode = Support::DragMode::Resize;
					resizeStartPoint = this->PointToScreen(e->Location);
					this->Capture = true;
				}
				else {
					dragMode = Support::DragMode::Move;
					this->previousLocation = e->Location;
					this->Capture = true;
				}
				isDragging = true;
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

		virtual void onMouseMove(Object^ sender, Windows::Forms::MouseEventArgs^ e) override {
			if (isDragging) {
				if (dragMode == Support::DragMode::Move) {
					this->Location = Drawing::Point(this->Left + e->X - dragOffsetX, this->Top + e->Y - dragOffsetY);
					this->Invalidate();
				}
				else if (dragMode == Support::DragMode::Resize) {
					Drawing::Point screenPoint = this->PointToScreen(e->Location);
					this->Width = Math::Max(this->Width + screenPoint.X - resizeStartPoint.X, ResizeHandleSize * 2);
					this->Height = Math::Max(this->Height + screenPoint.Y - resizeStartPoint.Y, ResizeHandleSize * 2);
					resizeStartPoint = screenPoint;
					this->Invalidate();
				}
			}
		}

		virtual void onMouseUp(Object^ sender, Windows::Forms::MouseEventArgs^ e) override {
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

		virtual void onMouseMove(Object^ sender, Windows::Forms::MouseEventArgs^ e) override {
			if (isDragging) {
				if (dragMode == Support::DragMode::Resize) {
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

					this->Invalidate();
				}
				else {
					DraggableRectangle::onMouseMove(sender, e);
				}
			}
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
				Windows::Forms::MenuItem^ addDoorItem = gcnew Windows::Forms::MenuItem("�������� �����", gcnew EventHandler(this, &Wall::OnAddFeature));
				Windows::Forms::MenuItem^ addWindowItem = gcnew Windows::Forms::MenuItem("�������� ����", gcnew EventHandler(this, &Wall::OnAddFeature));
				Windows::Forms::MenuItem^ addOpeningItem = gcnew Windows::Forms::MenuItem("�������� �����", gcnew EventHandler(this, &Wall::OnAddFeature));
				Windows::Forms::MenuItem^ deleteWallItem = gcnew Windows::Forms::MenuItem("������� �����", gcnew EventHandler(this, &Wall::OnDeleteWallSelected));

				menu->MenuItems->Add(addDoorItem);
				menu->MenuItems->Add(addWindowItem);
				menu->MenuItems->Add(addOpeningItem);
				menu->MenuItems->Add(deleteWallItem);

				menu->Show(this, e->Location);
			}
			FixedSideRectangle::OnMouseClick(e);
		}

		virtual void onMouseDown(Object^ sender, Windows::Forms::MouseEventArgs^ e) override {
			if (e->Button == System::Windows::Forms::MouseButtons::Left) {
				dragOffsetX = e->X;
				dragOffsetY = e->Y;

				if (IsInResizeZone(e->Location)) {
					dragMode = Support::DragMode::Resize;
					resizeStartPoint = this->PointToScreen(e->Location);
					this->Capture = true;
				}
				else {
					dragMode = Support::DragMode::Move;
					this->previousLocation = e->Location;
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
		WallFeature(Drawing::Color color, Support::Orientation orientation, int dimension)
			: FixedSideRectangle(color, orientation, dimension, dimension) {}

		WallFeature() : FixedSideRectangle() {};

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
			WallFeature^ rectangle = gcnew WallFeature();
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
				int orientationValue = Int32::Parse(reader->ReadElementString("FixedSide"));
				rectangle->orientation = (Support::Orientation)orientationValue;
				reader->ReadEndElement();
			}

			return rectangle;
		}

	protected:
		virtual void onMouseMove(Object^ sender, Windows::Forms::MouseEventArgs^ e) override {
			if (isDragging) {
				Wall^ wall = dynamic_cast<Wall^>(this->Parent);

				if (dragMode == Support::DragMode::Move) {
					int newX = this->Left + e->X - dragOffsetX;
					int newY = this->Top + e->Y - dragOffsetY;

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

		virtual void onMouseDown(Object^ sender, Windows::Forms::MouseEventArgs^ e) override {
			FixedSideRectangle::onMouseDown(sender, e);

			if (e->Button == System::Windows::Forms::MouseButtons::Left) {
				Wall^ wall = dynamic_cast<Wall^>(this->Parent);

				dragOffsetX = e->X;
				dragOffsetY = e->Y;

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

		if (featureType == "�������� �����") {
			if (this->orientation == Support::Orientation::Horizontal)
				newFeature = gcnew WallFeature(Drawing::Color::DarkRed, this->orientation, this->Height);
			else
				newFeature = gcnew WallFeature(Drawing::Color::DarkRed, this->orientation, this->Width);
		}
		else if (featureType == "�������� ����") {
			if (this->orientation == Support::Orientation::Horizontal)
				newFeature = gcnew WallFeature(Drawing::Color::LightSkyBlue, this->orientation, this->Height);
			else
				newFeature = gcnew WallFeature(Drawing::Color::LightSkyBlue, this->orientation, this->Width);
		}
		else if (featureType == "�������� �����") {
			if (this->orientation == Support::Orientation::Horizontal)
				newFeature = gcnew WallFeature(Drawing::Color::LightGray, this->orientation, this->Height);
			else
				newFeature = gcnew WallFeature(Drawing::Color::LightGray, this->orientation, this->Width);
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
		Wall^ rectangle = gcnew Wall();
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
			int orientationValue = Int32::Parse(reader->ReadElementString("FixedSide"));
			rectangle->orientation = (Support::Orientation)orientationValue;
			reader->ReadEndElement();
		}
		if (reader->Name == "Features") {

			while (!(reader->NodeType == XmlNodeType::EndElement && reader->Name == "Features") && reader->Read()) {
				if (reader->NodeType == XmlNodeType::Element) {
					WallFeature^ feature = WallFeature::deserialize(reader);
					rectangle->AddWallFeature(feature);
				}
			}
			reader->ReadEndElement();
		}

		return rectangle;
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
	}
}