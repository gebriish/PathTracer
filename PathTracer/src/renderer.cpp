#include "renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#include "utils.h"

vec3 Renderer::sample_square() const {
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

void Renderer::onRender(Camera& camera, Scene& scene) {

    uint32_t width = camera.getWidth();
    uint32_t height = camera.getHeight();
    double aspect_ratio = (double) width / height;

    unsigned char* imageData = new unsigned char[width * height * 3];

    vec3 forward = normalize(camera.lookAt() - camera.position());
    vec3 right   = cross(forward, vec3(0,1,0));
    vec3 up      = cross(right, forward);


    for(uint32_t j=0; j<height; j++) {
        
        std::clog << "\rScanlines remaining: " << height - j << ' ' << std::flush;
        
        for(uint32_t i=0; i<width; i++) {

            double pLen  = 1/tan(degrees_to_radians(camera.getFov()/2.0));
            double relativeX = double(i) / camera.getWidth();
            relativeX = relativeX * 2.0 - 1.0;            
            double relativeY = double(j) / camera.getHeight();
            relativeY = 1.0 - 2.0 * relativeY;
            relativeX *= aspect_ratio;


            vec3 rayDir  = forward * pLen + right * relativeX + up * relativeY;
            rayDir = normalize(rayDir);

            vec3 color(0.0);

            for(int i=0; i<Settings.Samples; i++) {
                vec3 sample_offset = sample_square();
                sample_offset[0] = sample_offset[0] / width;
                sample_offset[1] = sample_offset[1] / height;
                Ray r{camera.position(), rayDir + sample_offset};  
                color += getRayColor(r, Settings.Depth, scene);
            }
            
            color /= Settings.Samples;

            int pixel_index = (i + j * width) * 3;
            writeColor(imageData, color, pixel_index);
        }    
    }

    std::clog << "Done!\n";

    stbi_write_jpg("output.jpg", width, height, 3, imageData, 100);
    stbi_image_free(imageData);

    std::clog << "Image wrote!";
}

void Renderer::writeColor(unsigned char* img,const vec3& color, unsigned int pixel_index) {
    double r = fmax(fmin(color.x(), 1.0), 0.0);
    double g = fmax(fmin(color.y(), 1.0), 0.0);
    double b = fmax(fmin(color.z(), 1.0), 0.0);

    int rbytes = 255 * r;
    int gbytes = 255 * g;
    int bbytes = 255 * b;

    img[pixel_index + 0] = static_cast<unsigned char>(rbytes);
    img[pixel_index + 1] = static_cast<unsigned char>(gbytes);
    img[pixel_index + 2] = static_cast<unsigned char>(bbytes);   
}

bool scatterMaterial(const Material& mat, const Ray& r, const HitRecord& rec, vec3& attenuation, Ray& scattered) {
    
    vec3 scatter_direction;

    scatter_direction = random_unit_vector() + rec.normal;

    if (scatter_direction.near_zero())
        scatter_direction = rec.normal;

    scattered = Ray{rec.p, scatter_direction};


    attenuation = mat.base_color; 

    return true;
}

vec3 Renderer::getRayColor(const Ray& r, int depth, Scene& scene) {
    if (depth <= 0)
        return vec3(0);

    HitRecord rec;

    if (scene.hit(r, 0.001, infinity, rec)) {
        Ray scattered;
        vec3 attenuation;

        const Material& material = scene.getMaterial(rec.material_index);

        if (scatterMaterial(material, r, rec, attenuation, scattered)) {
            return attenuation * getRayColor(scattered, depth - 1, scene);
        }

        return vec3(0, 0, 0);
    }

    return vec3(0.8); // Background color
}
