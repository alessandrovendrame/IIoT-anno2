/******************************************************************************
**
** <auto-generated>
**     This code was generated by a tool: UaModeler
**     Runtime Version: 1.6.5, using .NET Server 3.0.0 template (version 2)
**
**     Changes to this file may cause incorrect behavior and will be lost if
**     the code is regenerated.
** </auto-generated>
**
** Copyright (c) 2006-2021 Unified Automation GmbH All rights reserved.
**
** Software License Agreement ("SLA") Version 2.7
**
** Unless explicitly acquired and licensed from Licensor under another
** license, the contents of this file are subject to the Software License
** Agreement ("SLA") Version 2.7, or subsequent versions
** as allowed by the SLA, and You may not copy or use this file in either
** source code or executable form, except in compliance with the terms and
** conditions of the SLA.
**
** All software distributed under the SLA is provided strictly on an
** "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
** AND LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
** LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
** PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the SLA for specific
** language governing rights and limitations under the SLA.
**
** Project: .NET OPC UA SDK information model for namespace http://yourorganisation.org/CPU/
**
** Description: OPC Unified Architecture Software Development Kit.
**
** The complete license agreement can be found here:
** http://unifiedautomation.com/License/SLA/2.7/
**
** Created: 10.06.2021
**
******************************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using UnifiedAutomation.UaBase;
using UnifiedAutomation.UaServer;

namespace its.itsVendrame
{
    #region CPU
    /// <summary>
    /// </summary>
    [UaTypeDefinition(NodeId=ObjectTypes.CPU, NamespaceUri=its.itsVendrame.Namespaces.itsVendrame)]
    public partial class CPU : BaseObjectModel
    {
        #region Constructors
        /// <summary>
        /// Initializes a new instance of the <see cref="CPU" /> class.
        /// </summary>
        public CPU() : this((CPU)null)
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="CPU" /> class.
        /// </summary>
        /// <param name="template">The template.</param>
        public CPU(CPU template) : base(template)
        {
            if (template == null)
            {
            }
            else
            {
                CpuPercentage = template.CpuPercentage;
                DiskSpaceUsed = template.DiskSpaceUsed;
                MemoryUsed = template.MemoryUsed;
                RuntimePrograms = template.RuntimePrograms == null ? null : template.RuntimePrograms.Clone() as string;
            }
        }
        #endregion

        #region Public Properties
        /// <summary>
        /// Gets or sets the CpuPercentage
        /// </summary>
        [UaInstanceDeclaration(NamespaceUri = Namespaces.itsVendrame)]
        public double CpuPercentage { get; set; }

        /// <summary>
        /// Gets or sets the DiskSpaceUsed
        /// </summary>
        [UaInstanceDeclaration(NamespaceUri = Namespaces.itsVendrame)]
        public double DiskSpaceUsed { get; set; }

        /// <summary>
        /// Gets or sets the MemoryUsed
        /// </summary>
        [UaInstanceDeclaration(NamespaceUri = Namespaces.itsVendrame)]
        public int MemoryUsed { get; set; }

        /// <summary>
        /// Gets or sets the RuntimePrograms
        /// </summary>
        [UaInstanceDeclaration(NamespaceUri = Namespaces.itsVendrame)]
        public string RuntimePrograms { get; set; }


        #endregion
    }
    #endregion



}
