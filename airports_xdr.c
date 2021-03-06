/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "airports.h"

bool_t
xdr_nametype_air (XDR *xdrs, nametype_air *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, objp, MAXLEN))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_airList_air (XDR *xdrs, airList_air *objp)
{
	register int32_t *buf;

	 if (!xdr_pointer (xdrs, (char **)objp, sizeof (struct airNode_air), (xdrproc_t) xdr_airNode_air))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_geoLocation (XDR *xdrs, geoLocation *objp)
{
	register int32_t *buf;

	 if (!xdr_double (xdrs, &objp->longitude))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->latitude))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_nearAirport (XDR *xdrs, nearAirport *objp)
{
	register int32_t *buf;

	 if (!xdr_nametype_air (xdrs, &objp->code))
		 return FALSE;
	 if (!xdr_nametype_air (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_nametype_air (xdrs, &objp->state))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->dist))
		 return FALSE;
	 if (!xdr_geoLocation (xdrs, &objp->loc))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_airNode_air (XDR *xdrs, airNode_air *objp)
{
	register int32_t *buf;

	 if (!xdr_nearAirport (xdrs, &objp->p))
		 return FALSE;
	 if (!xdr_airList_air (xdrs, &objp->next))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_nearest_results_air (XDR *xdrs, nearest_results_air *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->err))
		 return FALSE;
	switch (objp->err) {
	case 0:
		 if (!xdr_airList_air (xdrs, &objp->nearest_results_air_u.x))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}
