struct Vec3 {
    float x;
    float y;
    float w;
};

inline Vec3 cross(const Vec3& a, const Vec3& b) {
    return {
        a.y * b.w - a.w * b.y,
        a.w * b.x - a.x * b.w,
        a.x * b.y - a.y * b.x
    };
}