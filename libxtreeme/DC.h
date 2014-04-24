#ifndef Xtreeme_DC_h
#define Xtreeme_DC_h

#include <libxtypes/IRI.h>

namespace DC
{
	const QString Base("http://purl.org/dc/terms/");

	// Classes
	const X::IRI Agent                        (Base + "Agent");
	const X::IRI AgentClass                   (Base + "AgentClass");
	const X::IRI BibliographicResource        (Base + "BibliographicResource");
	const X::IRI FileFormat                   (Base + "FileFormat");
	const X::IRI Frequency                    (Base + "Frequency");
	const X::IRI Jurisdiction                 (Base + "Jurisdiction");
	const X::IRI LicenseDocument              (Base + "LicenseDocument");
	const X::IRI LinguisticSystem             (Base + "LinguisticSystem");
	const X::IRI Location                     (Base + "Location");
	const X::IRI LocationPeriodOrJurisdiction (Base + "LocationPeriodOrJurisdiction");
	const X::IRI MediaType                    (Base + "MediaType");
	const X::IRI MediaTypeOrExtent            (Base + "MediaTypeOrExtent");
	const X::IRI MethodOfAccrual              (Base + "MethodOfAccrual");
	const X::IRI MethodOfInstruction          (Base + "MethodOfInstruction");
	const X::IRI PeriodOfTime                 (Base + "PeriodOfTime");
	const X::IRI PhysicalMedium               (Base + "PhysicalMedium");
	const X::IRI PhysicalResource             (Base + "PhysicalResource");
	const X::IRI Policy                       (Base + "Policy");
	const X::IRI ProvenanceStatement          (Base + "ProvenanceStatement");
	const X::IRI RightsStatement              (Base + "RightsStatement");
	const X::IRI SizeOrDuration               (Base + "SizeOrDuration");
	const X::IRI Standard                     (Base + "Standard");
}

#endif
