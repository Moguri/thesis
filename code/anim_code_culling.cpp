void KX_Scene::UpdateAnimations(double curtime)
{
	for (int i=0; i<m_animatedlist->GetCount(); ++i) {
		KX_GameObject *gameobj, *child;
		bool needs_update;

		gameobj = (KX_GameObject*)m_animatedlist->GetValue(i);

		// Non-armature updates are fast enough, so just update them
		needs_update = gameobj->GetGameObjectType() != SCA_IObject::OBJ_ARMATURE;

		if (!needs_update) {
			// If we got here, we're looking to update an armature, so check its
			// children meshes to see if we need to bother with a more expensive
			// pose update
			CListValue *children = gameobj->GetChildren();

			bool has_mesh = false, has_non_mesh = false;

			// Check for meshes that haven't been culled
			for (int j=0; j<children->GetCount(); ++j) {
				child = (KX_GameObject*)children->GetValue(j);

				if (!child->GetCulled()) {
					needs_update = true;
					break;
				}

				if (child->GetMeshCount() == 0)
					has_non_mesh = true;
				else
					has_mesh = true;
			}

			// If we didn't find a non-culled mesh, check to see
			// if we even have any meshes, and update if this
			// armature has only non-mesh children.
			if (!needs_update && !has_mesh && has_non_mesh)
				needs_update = true;

			children->Release();
		}

		if (needs_update)
			gameobj->UpdateActionManager(curtime);
	}
}
