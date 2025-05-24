#include "pch.h"
#include "MySCP.h"

MySCP::MySCP()
{

}

MySCP::~MySCP()
{

}

int MySCP::startSCP()
{
	// ���� SCP �� AE Title �ͼ����˿�
	setAETitle("SCP_DEMO");
	setPort(11112);
	setVerbosePCMode(true);

	// ����һ�� OFList<OFString> ����Ӵ����﷨
	OFList<OFString> transferSyntaxes;
	transferSyntaxes.push_back(UID_LittleEndianExplicitTransferSyntax);

	// ���� addPresentationContext ����
	addPresentationContext(UID_UltrasoundImageStorage, transferSyntaxes);

	std::cout << "C-STORE Demo SCP is running. Waiting for incoming requests..." << std::endl;

	// ��ʼ�����ʹ�������
	OFCondition status = listen();
	if (!status.good())
	{
		std::cerr << "Failed to start SCP listener: " << status.text() << std::endl;
		return 1;
	}

	return 0;
}

void MySCP::stopSCP()
{
	stopAfterCurrentAssociation();
}

OFCondition MySCP::handleIncomingCommand(T_DIMSE_Message* incomingMsg, const DcmPresentationContextInfo& presInfo)
{
	//�ú�����δ��������scu��dataset��ֻ������������Ϣ
	OFCondition cond;
	OFCondition status = EC_IllegalParameter;
	// ���� C-ECHO ����
	if ((incomingMsg->CommandField == DIMSE_C_ECHO_RQ) && (presInfo.abstractSyntax == UID_VerificationSOPClass))
	{
		DCMNET_DEBUG("C-ECHO");
		std::cout << "C-ECHO" << std::endl;;
		cond = handleECHORequest(incomingMsg->msg.CEchoRQ, presInfo.presentationContextID);
	}
	else if ((incomingMsg->CommandField == DIMSE_C_STORE_RQ))
	{
		// ���� C-STORE ����
		DCMNET_DEBUG("C-STORE");
		std::cout << "C-STORE" << std::endl;;
		// ��������
		T_DIMSE_C_StoreRQ& storeReq = incomingMsg->msg.CStoreRQ;
		T_DIMSE_C_StoreRSP storeRsp;
		storeRsp.MessageIDBeingRespondedTo = storeReq.MessageID;

		DcmDataset* reqDataset = NULL;
		T_ASC_PresentationContextID presID = presInfo.presentationContextID;
		status = receiveDIMSEDataset(&presID, &reqDataset);

		// ���ͻ�Ӧ��Ϣ
		Uint16 rspStatusCode;
		if (status.good())
		{
			rspStatusCode = STATUS_Success;
			
			OFString PatientName;
			OFCondition result = reqDataset->findAndGetOFString(DCM_PatientName, PatientName);
			if (result.good())
			{
				DCMNET_DEBUG("PatientName: " << PatientName);
				std::cout << "PatientName: " << PatientName << std::endl;
			}
			else
			{
				DCMNET_DEBUG("No PatientName being found");
				std::cout << "No PatientName being found" << std::endl;
			}

			DcmElement *element = NULL;
			result = reqDataset->findAndGetElement(DCM_PixelData, element);
			if (result.good())
			{
				Uint16 rows, columns;
				result = reqDataset->findAndGetUint16(DCM_Rows, rows);
				if (result.good())
				{
					result = reqDataset->findAndGetUint16(DCM_Columns, columns);
					if (result.good())
					{
						Uint8* pixData8;
						result = element->getUint8Array(pixData8);
						if (result.good())
						{
							Uint16 samplesPerPixel = 1;
							reqDataset->findAndGetUint16(DCM_SamplesPerPixel, samplesPerPixel);

							if (samplesPerPixel == 3) // RGB
							{
								// ע�⣺DICOM��RGB����ͨ����������R1G1B1R2G2B2...
								cv::Mat imag_rgb(rows, columns, CV_8UC3, pixData8);
								cv::Mat imag_bgr;
								cv::cvtColor(imag_rgb, imag_bgr, cv::COLOR_RGB2BGR);
								cv::imshow("CM-70 Screen", imag_bgr);
							}else {
								cv::Mat imag = cv::Mat(rows, columns, CV_8U, pixData8);
								cv::imshow("CM-70 Screen", imag);
							}
							cv::waitKey(1);
						}else {
							std::cout << "Couldn't find Pixel Data Array" << std::endl;
						}												
					}
					else
					{
						std::cout << "Couldn't find Columns" << std::endl;
					}
				}
				else
				{
					std::cout << "Couldn't find Rows" << std::endl;
				}
			}		
			else
			{
				std::cout << "Couldn't find Pixel Data Element" << std::endl;
			}
		}
		else if (status == DIMSE_OUTOFRESOURCES)
		{
			rspStatusCode = STATUS_STORE_Refused_OutOfResources;
		}
		else
		{
			storeRsp.DimseStatus = STATUS_STORE_Error_CannotUnderstand;
		}
		sendSTOREResponse(presInfo.presentationContextID, storeReq, rspStatusCode);
		if (reqDataset != nullptr) {
			delete reqDataset;
			reqDataset = nullptr;
		}
	}
	else
	{
		// ��������ȫ���ܾ�        
		OFString tempStr;
		DCMNET_ERROR("Cannot handle this kind of DIMSE command (0x"
			<< STD_NAMESPACE hex << STD_NAMESPACE setfill('0') << STD_NAMESPACE setw(4)
			<< OFstatic_cast(unsigned int, incomingMsg->CommandField) << ")");
		DCMNET_DEBUG(DIMSE_dumpMessage(tempStr, *incomingMsg, DIMSE_INCOMING));
		cond = DIMSE_BADCOMMANDTYPE;
	}
	return cond;
}


