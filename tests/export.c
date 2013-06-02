#include "clar.h"

#include "stl.h"
#include "bsp.h"

char cube_stl_path[] = CLAR_FIXTURE_PATH "cube.stl";
stl_object *cube_stl = NULL;
klist_t(poly) *cube_polys = NULL;
bsp_node_t *cube_tree = NULL;

void test_export__initialize(void) {
	cube_stl = stl_read_file(cube_stl_path, 1);
	cl_assert_(cube_stl != NULL, "Failed to read cube.");
	cl_assert_(cube_stl->facet_count >= 12, "Cube should be >= 12 facets.");

	for(int i = 0; i < cube_stl->facet_count; i++) {
		poly_t *poly = poly_make_triangle(cube_stl->facets[i].vertices[0],
										  cube_stl->facets[i].vertices[1],
										  cube_stl->facets[i].vertices[2]);
		cl_assert(poly != NULL);
		*kl_pushp(poly, cube_polys) = poly;
	}
	cube_tree = bsp_build(NULL, cube_polys);
	cl_assert(cube_tree);
}

void test_export__cleanup(void) {
	if(cube_stl) stl_free(cube_stl);
	if(cube_polys) kl_destroy(poly, cube_polys);
	// TODO: free_bsp(bsp)
}
