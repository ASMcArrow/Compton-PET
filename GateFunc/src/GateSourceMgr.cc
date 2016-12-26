#include "GateSourceMgr.hh"
#include "GateClock.hh"

GateSourceMgr::GateSourceMgr()
{
    Sources.clear();
    SelectedSource = 0;
}

GateSourceMgr::~GateSourceMgr()
{
    for( size_t i = 0; i != Sources.size(); i++ )
        if( Sources[i] )
            delete Sources[i];
    Sources.clear();

}

void GateSourceMgr::AddSource(GateVSource* source)
{
    Sources.push_back(source);
}

GateVSource* GateSourceMgr::GetNextSource()
{
    // the method decides which is the source that has to be used for this event
    GateVSource* pFirstSource = 0;
    m_firstTime = -1.;

    G4double aTime;

        // if there is at least one source
        // make a competition among all the available sources
        // the source that proposes the shortest interval for the next event wins
        GateVSourceVector::iterator itr;
        for( itr = mSources.begin(); itr != mSources.end(); ++itr )
        {
            aTime = (*itr)->GetNextTime( m_time ); // compute random time for this source
              if( m_firstTime < 0. || ( aTime < m_firstTime ) )
            {
                m_firstTime = aTime;
                pFirstSource = *itr;
            }
        }
    }

    return pFirstSource;
}

G4int GateSourceMgr::PrepareNextEvent( G4Event* event )
{
    // GateDebugMessage("Acquisition", 0, "PrepareNextEvent "  << event->GetEventID()
    //                    << " at time " << m_time/s << " sec.\n");

    GateSteppingAction* myAction = (GateSteppingAction *) ( GateRunManager::GetRunManager()->GetUserSteppingAction() );
    TrackingMode theMode =myAction->GetMode();
    m_currentSources.clear();

    G4int numVertices = 0;

    if ( (theMode == 1)  || (theMode == 2) )
    {
        GateRTPhantomMgr::GetInstance()->UpdatePhantoms(m_time); /* PY Descourt 11/12/2008 */

        if( mVerboseLevel > 1 )
            G4cout << "GateSourceMgr::PrepareNextEvent\n";

        // ask the source for this event
        if( mVerboseLevel > 1 )
            G4cout << "GateSourceMgr::PrepareNextEvent : GetNextSource() \n";
        GateVSource* source = GetNextSource();

        if( source )
        {
            // obsolete: to avoid the initialization phase for the source if it's the same as
            // the previous event (always the same with only 1 source). Not needed now with one gps
            // per source
            if( source != m_previousSource ) m_needSourceInit = true;
            m_previousSource = source;

            // save the information, that can then be asked during the analysis phase
            m_currentSources.push_back( source );

            // update the internal time
            m_time += m_firstTime;


            GateApplicationMgr* appMgr = GateApplicationMgr::GetInstance();
            // G4double timeStop           = appMgr->GetTimeStop();
            appMgr->SetCurrentTime(m_time);

            if( mVerboseLevel > 1 )
                G4cout << "GateSourceMgr::PrepareNextEvent :  m_time (s) " << m_time/s
                       << "  m_timeLimit (s) " << m_timeLimit/s << Gateendl;

            // Warning: the comparison  m_time <= m_timeLimit should be wrong due to decimal floating point problem

            /*  if (((!appMgr->IsAnAmountOfPrimariesPerRunModeEnabled() && ( m_time <= m_timeLimit ))
              || (appMgr->IsAnAmountOfPrimariesPerRunModeEnabled()
              && (mNbOfParticleInTheCurrentRun < appMgr->GetNumberOfPrimariesPerRun()) ))
              && ( m_time <= timeStop ) ) */
            //      if( (  m_timeLimit - m_time >= -0.001 ) && ( m_time <= timeStop ) )
            // G4cout << m_time - m_timeLimit<<"   "<<m_firstTime<<"    "<<m_firstTime*(1-1.E-10) <<"  "<< (m_time - m_timeLimit) - m_firstTime << Gateendl;

            //          if( !appMgr->IsTotalAmountOfPrimariesModeEnabled() && ( m_time <= m_timeLimit ) )
            if( m_time <= m_timeLimit )
                //             || (appMgr->IsTotalAmountOfPrimariesModeEnabled() && appMgr->IsAnAmountOfPrimariesPerRunModeEnabled() && (mNbOfParticleInTheCurrentRun < appMgr->GetNumberOfPrimariesPerRun()))
                //             || (appMgr->IsTotalAmountOfPrimariesModeEnabled() && ( fabs(m_time - m_timeLimit - m_firstTime) > m_firstTime*0.5  ) && ( m_time - timeStop  <= m_firstTime )))
            {
                if( mVerboseLevel > 1 )
                    G4cout << "GateSourceMgr::PrepareNextEvent : source selected <"
                           << source->GetName() << ">\n";

                // transmit the time to the source and ask it to generate the primary vertex
                source->SetTime( m_time );
                source->SetNeedInit( m_needSourceInit );
                SetWeight(appMgr->GetWeight());
                source->SetSourceWeight(GetWeight());
                mNumberOfEventBySource[source->GetSourceID()+1]+=1;
                numVertices = source->GeneratePrimaries( event );
            }
            else {
                if( mVerboseLevel > 0 )
                    G4cout << "GateSourceMgr::PrepareNextEvent : m_time > m_timeLimit. No vertex generated\n";

                /*if(m_time <= timeStop){
              m_time-=m_firstTime;
              appMgr->SetCurrentTime(m_time);
            }*/
            }
        }
        else {
            G4cout << "GateSourceMgr::PrepareNextEvent : WARNING : GateSourceMgr::GetNextSource gave no source\n";
        }

        m_needSourceInit = false;

        mNbOfParticleInTheCurrentRun++;
    } // normal or Tracker Modes

    if ( theMode == 3 ) // detector mode
    {
        m_currentSources.push_back(m_fictiveSource);
        //G4cout << "GateSourceMgr::PrepareNextEvent :   m_fictiveSource = " << m_fictiveSource << Gateendl;
        numVertices = m_fictiveSource->GeneratePrimaries(event);
        m_fictiveSource->SetTime(m_time); // time has been set in GeneratePrimaries

        //	G4cout << "GateSourceMgr::PrepareNextEvent :::::::      Time " << m_time/s << " time limit " << m_timeLimit/s << Gateendl;

        if (m_time > m_timeLimit) {  numVertices = 0 ;}

    }

    if( ( m_time + 5.0 * m_firstTime ) > m_timeLimit ) {  m_launchLastBuffer = true;}

    if (mVerboseLevel>1)
        G4cout << "GateSourceMgr::PrepareNextEvent : numVertices : " << numVertices << Gateendl;
    return numVertices;
}
