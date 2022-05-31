#include <iostream>

using std::cout;
using std::endl;

enum imageType {
  LSAT,
  SPOT
};

class Image {
public:

  virtual auto Draw()->void = 0;
  static auto FindAndClone(imageType)->Image *;
  virtual ~Image() = default;

protected:

  virtual auto ReturnType()->imageType = 0;
  virtual auto Clone()->Image *        = 0;

  // As each subclass of Image is declared, it registers its prototype
  static auto  AddPrototype(Image *image)->void {
    _prototypes[_nextSlot++] = image;
  }

private:

  // addPrototype() saves each registered prototype here
  static Image *_prototypes[10];
  static int _nextSlot;
};

Image *Image::_prototypes[];
int    Image::_nextSlot;

// Client calls this public static member function when it needs an instance
// of an Image subclass
auto Image::FindAndClone(imageType type)->Image *

{
  for (auto i = 0; i < _nextSlot; i++)
    if (_prototypes[i]->ReturnType() == type) return _prototypes[i]->Clone();

  return nullptr;
}

class LandSatImage
  : public Image {
public:

  virtual auto ReturnType()->imageType override {
    return LSAT;
  }

  virtual auto Draw()->void override {
    cout << "LandSatImage::draw " << _id << endl;
  }

  // When clone() is called, call the one-argument ctor with a dummy arg
  virtual auto Clone()->Image * override {
    return new LandSatImage(1);
  }

protected:

  // This is only called from clone()
  explicit LandSatImage(int dummy) {
    _id = _count++;
  }

private:

  // Mechanism for initializing an Image subclass - this causes the
  // default ctor to be called, which registers the subclass's prototype
  static LandSatImage _landSatImage;

  // This is only called when the private static data member is initiated
  LandSatImage() {
    AddPrototype(this);
  }

public:

  virtual ~LandSatImage() override = default;

private:

  // Nominal "state" per instance mechanism
  int _id;
  static int _count;
};

// Register the subclass's prototype
LandSatImage LandSatImage::_landSatImage;

// Initialize the "state" per instance mechanism
int LandSatImage::_count = 1;

class SpotImage
  : public Image {
public:

  virtual auto ReturnType()->imageType override {
    return SPOT;
  }

  virtual auto Draw()->void override {
    cout << "SpotImage::draw " << _id << endl;
  }

  virtual auto Clone()->Image * override {
    return new SpotImage(1);
  }

protected:

  explicit SpotImage(int dummy) {
    _id = _count++;
  }

private:

  SpotImage() {
    AddPrototype(this);
  }

public:

  virtual ~SpotImage() override = default;

private:

  static SpotImage _spotImage;
  static int _count;
  int _id;
};

SpotImage SpotImage::_spotImage;
int SpotImage::_count = 1;

// Simulated stream of creation requests
const int NUM_IMAGES = 8;
imageType input[NUM_IMAGES] { LSAT, LSAT, LSAT, SPOT, LSAT, SPOT, SPOT, LSAT };


auto main(int argc, char *argv[])->int
{
  Image *images[NUM_IMAGES];

  // Given an image type, find the right prototype, and return a clone
  for (auto i = 0; i < NUM_IMAGES; i++) images[i] = Image::FindAndClone(input[i]);

  // Demonstrate that correct image objects have been cloned
  for (auto i = 0; i < NUM_IMAGES; i++) images[i]->Draw();

  // Free the dynamic memory
  for (auto i = 0; i < NUM_IMAGES; i++) delete images[i];
  getchar();
  return EXIT_SUCCESS;
}
